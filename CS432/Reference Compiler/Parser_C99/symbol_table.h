#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

// Represents a type in the C language
typedef struct Type {
    enum {
        TYPE_BASE,
        TYPE_ARRAY,
        TYPE_POINTER,
        TYPE_FUNCTION,
        TYPE_STRUCT,
        TYPE_UNION
    } kind;
    union {
        char *base_name; // For TYPE_BASE (e.g., "int", "double")
        struct { struct Type *element_type; int size; } array_info; // For TYPE_ARRAY
        struct Type *points_to; // For TYPE_POINTER
        struct { // For struct/union
            char *name;
            struct Symbol *members; // Linked list of members
        } record_info;
        struct { // For TYPE_FUNCTION
            struct Type *return_type;
            struct Symbol *params; // Linked list of parameter symbols
        } function_info;
    } data;
} Type;

// Represents a single entry in the symbol table (a variable, function, etc.)
typedef struct Symbol {
    enum {
        SYM_VARIABLE,
        SYM_TYPENAME,
        SYM_FUNCTION
    } kind;
    char *name;
    Type *type;
    struct Symbol *next; // For linking symbols in the same scope
} Symbol;

/* --- Function Prototypes --- */

// Initializes the symbol table
void init_symbol_table();

// Inserts a new symbol into the symbol table
void insert_symbol(const char *name, Type *type, int kind);

// Looks up a symbol in the symbol table
Symbol* lookup_symbol(const char *name);

// Prints the contents of the symbol table
void print_symbol_table();

// Helper functions for creating and managing types
Type* create_base_type(const char *base_name);
Type* create_array_type(Type *element_type, int size);
Type* create_record_type(int kind, const char *name, Symbol *members);
Type* create_pointer_type(Type *points_to);
Type* create_function_type(Type *return_type, Symbol *params);
void free_type(Type *type);

#endif // SYMBOL_TABLE_H