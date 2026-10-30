#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

// The head of our single, global symbol table
Symbol *symbol_table_head = NULL;

void init_symbol_table() {
    symbol_table_head = NULL;
}

void insert_symbol(const char *name, Type *type, int kind) {
    //printf("Inserting symbol: %s of kind %s\n", name,
    //       (kind == SYM_VARIABLE) ? "VARIABLE" : "TYPENAME");
    // Check for re-declaration
    for (Symbol *s = symbol_table_head; s != NULL; s = s->next) {
        if (strcmp(s->name, name) == 0) {
            // In a real compiler, you'd use yyerror here with line numbers
            fprintf(stderr, "Semantic Error: Redeclaration of identifier '%s'.\n", name);
            return;
        }
    }

    Symbol *new_symbol = (Symbol*) malloc(sizeof(Symbol));
    if (!new_symbol) {
        fprintf(stderr, "Fatal: Out of memory for new symbol\n");
        exit(1);
    }
    new_symbol->name = strdup(name);
    new_symbol->kind = kind;
    new_symbol->type = type; // Assign the pointer to the complex type
    new_symbol->next = symbol_table_head;
    symbol_table_head = new_symbol;
}

Symbol* lookup_symbol(const char *name) {
    for (Symbol *s = symbol_table_head; s != NULL; s = s->next) {
        if (strcmp(s->name, name) == 0) {
            return s; // Found it!
        }
    }
    return NULL; // Not found in any scope
}

void print_symbol_table() {
    printf("\n--- Symbol Table Contents ---\n");
    if (symbol_table_head == NULL) {
        printf("  (empty)\n");
    } else {
        Symbol *s = symbol_table_head;
        while (s != NULL) {
            printf("  Name: %-15s, Kind: %s", s->name,
                   (s->kind == SYM_VARIABLE) ? "VARIABLE" : 
                   (s->kind == SYM_FUNCTION) ? "FUNCTION" : 
                   (s->kind == SYM_TYPENAME) ? "TYPENAME" : "UNKNOWN");
            // TODO: print the full type information here
            if (s->type && s->type->kind == TYPE_FUNCTION) {
                printf(", Type: Function returning %s", s->type->data.function_info.return_type->data.base_name);
            } else if (s->type && s->type->kind == TYPE_POINTER) {
                // Basic pointer printing. A full implementation would recurse for e.g. int**
                printf(", Type: Pointer to %s", s->type->data.points_to->data.base_name);
            } else if (s->type && s->type->kind == TYPE_BASE) {
                 printf(", Type: %s", s->type->data.base_name);
            } else if (s->type) {
                 printf(", Type: (Complex type info)");
            } else {
                printf(", Type: (unknown)");
            }
            printf("\n");
            s = s->next;
        }
    }
    printf("-----------------------------\n");
}

/* --- Type Management Functions --- */

Type* create_base_type(const char *base_name) {
    Type *new_type = (Type*) malloc(sizeof(Type));
    new_type->kind = TYPE_BASE;
    new_type->data.base_name = strdup(base_name);
    return new_type;
}

Type* create_array_type(Type *element_type, int size) {
    Type *new_type = (Type*) malloc(sizeof(Type));
    new_type->kind = TYPE_ARRAY;
    new_type->data.array_info.element_type = element_type;
    new_type->data.array_info.size = size;
    return new_type;
}

Type* create_record_type(int kind, const char *name, Symbol *members) {
    Type *new_type = (Type*) malloc(sizeof(Type));
    new_type->kind = kind; // TYPE_STRUCT or TYPE_UNION
    new_type->data.record_info.name = name ? strdup(name) : NULL;
    new_type->data.record_info.members = members;
    return new_type;
}

Type* create_pointer_type(Type *points_to) {
    Type *new_type = (Type*) malloc(sizeof(Type));
    new_type->kind = TYPE_POINTER;
    new_type->data.points_to = points_to;
    return new_type;
}

Type* create_function_type(Type *return_type, Symbol *params) {
    Type *new_type = (Type*) malloc(sizeof(Type));
    new_type->kind = TYPE_FUNCTION;
    new_type->data.function_info.return_type = return_type;
    new_type->data.function_info.params = params;
    return new_type;
}

void free_type(Type *type) {
    if (!type) return;

    switch (type->kind) {
        case TYPE_BASE:
            free(type->data.base_name);
            break;
        case TYPE_ARRAY:
            // Recursively free the element type
            free_type(type->data.array_info.element_type);
            break;
        case TYPE_POINTER:
            // Recursively free the pointed-to type
            free_type(type->data.points_to);
            break;
        case TYPE_FUNCTION:
            free_type(type->data.function_info.return_type);
            Symbol *param = type->data.function_info.params;
            while (param) {
                Symbol *temp = param;
                param = param->next;
                free(temp->name);
                free_type(temp->type);
                free(temp);
            }
            break;
        case TYPE_STRUCT:
        case TYPE_UNION:
            if (type->data.record_info.name) free(type->data.record_info.name);
            Symbol *member = type->data.record_info.members;
            while (member) {
                Symbol *temp = member;
                member = member->next;
                free(temp->name);
                free_type(temp->type);
                free(temp);
            }
            break;
    }
    free(type);
}