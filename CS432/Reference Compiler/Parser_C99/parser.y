%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h" // Include our new symbol table header
/* AST Node Structure */
typedef struct ASTNode {
    char *node_type;
    char *value;
    int num_children;
    struct ASTNode **children;
    Type *type; // Add this field to carry type information
} ASTNode;

/* Function Prototypes */
ASTNode* create_node(const char *node_type, const char *value, int num_children, ...);
void print_ast(ASTNode *node, int level);
void free_ast(ASTNode *node);
Type* get_base_type_from_specifiers(ASTNode* specifiers_node);
char* get_declarator_name(ASTNode* declarator_node);
Type* build_declarator_type(Type* base_type, ASTNode* declarator_node);


/* External declarations from the lexer */
extern int yylex();
extern int line_count;
extern char* yytext;
extern FILE* yyin;

void yyerror(const char *s);

/* Root of the AST */
ASTNode *ast_root = NULL;
int is_typedef_declaration = 0; // Flag to track typedef context

%}

/* Yacc/Bison Union for semantic values */
%union {
    char *str;
    struct ASTNode *node;
}

/* Token Definitions */
/* The lexer will return these token types */
%token <str> IDENTIFIER INT_CONST FLOAT_CONST CHAR_CONST STRING_LITERAL TYPENAME

/* Keywords */
%token KEYWORD_BREAK KEYWORD_CASE KEYWORD_CONST
%token KEYWORD_CONTINUE KEYWORD_DEFAULT KEYWORD_DO KEYWORD_ELSE
%token KEYWORD_ENUM
%token KEYWORD_IF 
%token KEYWORD_RESTRICT KEYWORD_RETURN
%token KEYWORD_SIZEOF  KEYWORD_STRUCT KEYWORD_SWITCH
%token KEYWORD_TYPEDEF KEYWORD_UNION
%token KEYWORD_VOLATILE KEYWORD_WHILE
%token KEYWORD_FOR

/* Operators */
%token OP_INCREMENT OP_DECREMENT
%token  OP_SHIFT_LEFT OP_SHIFT_RIGHT
%token OP_LE OP_GE OP_EQ OP_NE OP_AND OP_OR
%token OP_ADD_ASSIGN OP_SUB_ASSIGN OP_MUL_ASSIGN OP_DIV_ASSIGN OP_MOD_ASSIGN

/* Single-character tokens can be used directly as characters */
/* e.g. '+' '-' '*' '/' '%' '=' '<' '>' '&' '|' '^' '~' '!' */

/* Keywords with string values (for type specifiers) */
%token <str> KEYWORD_CHAR KEYWORD_DOUBLE KEYWORD_FLOAT KEYWORD_INT KEYWORD_LONG
%token <str> KEYWORD_SHORT KEYWORD_SIGNED KEYWORD_UNSIGNED KEYWORD_VOID

/* Type Definitions for grammar rules */
%type <node> program external_declaration function_definition declaration
%type <node> declaration_specifiers storage_class_specifier init_declarator declarator pointer
%type <node> direct_declarator parameter_type_list parameter_list parameter_declaration type_name abstract_declarator direct_abstract_declarator type_qualifier
%type <node> compound_statement block_item_list block_item statement expression_statement
%type <node> struct_or_union_specifier struct_or_union struct_declaration_list struct_declaration initializer initializer_list enum_specifier enumerator_list enumerator
%type <node> specifier_qualifier_list struct_declarator_list struct_declarator
%type <node> assignment_expression_opt parameter_type_list_opt
%type <node> selection_statement iteration_statement labeled_statement jump_statement expression assignment_expression
%type <node> expression_opt
%type <node> type_specifier_node
%type <node> conditional_expression logical_or_expression logical_and_expression
%type <node> inclusive_or_expression exclusive_or_expression and_expression
%type <node> equality_expression relational_expression shift_expression
%type <node> additive_expression multiplicative_expression cast_expression
%type <node> unary_expression postfix_expression primary_expression argument_expression_list
%type <str> type_specifier unary_operator assignment_operator
%type <node> init_declarator_list

%nonassoc LOWER_THAN_ELSE
%nonassoc KEYWORD_ELSE

%%

/* Grammar Rules */

program
    : external_declaration { ast_root = create_node("Program", NULL, 1, $1); }
    | program external_declaration { $$ = create_node("Program", NULL, 2, $1, $2); ast_root = $$; }
    ;

external_declaration
    : function_definition { $$ = $1; }
    | declaration         { $$ = $1; }
    ;

function_definition
    : declaration_specifiers declarator compound_statement
      {
        char* func_name = get_declarator_name($2);
        if (func_name) {
            Type* return_type = get_base_type_from_specifiers($1);
            Type* func_type = create_function_type(return_type, NULL);
            insert_symbol(func_name, func_type, SYM_FUNCTION);
            free(func_name);
        }
        $$ = create_node("FunctionDefinition", NULL, 3, $1, $2, $3);
      }
    ;

declaration
    : declaration_specifiers init_declarator_list ';'
      { 
        // This is now the central point for variable insertion.
        // We have both the type specifiers ($1) and the list of declarators ($2).
        Type* base_type = get_base_type_from_specifiers($1);
        ASTNode* declarator_list = $2;
        // The list is built backwards, so we traverse it to insert symbols.
        while(declarator_list) {
            ASTNode* declarator = declarator_list->children[0];
            char* name = get_declarator_name(declarator);
            if (name) {
                insert_symbol(name, base_type, is_typedef_declaration ? SYM_TYPENAME : SYM_VARIABLE);
                free(name);
            }
            if (declarator_list->num_children > 1) {
                declarator_list = declarator_list->children[1];
            } else {
                break;
            }
        }
        // Note: We don't free base_type here because multiple variables might share it.
        $$ = create_node("Declaration", NULL, 2, $1, $2);
      }
    ;

declaration_specifiers
    : storage_class_specifier { $$ = $1; }
    | type_specifier_node { $$ = $1; }
    | type_qualifier { $$ = $1; }
    | storage_class_specifier declaration_specifiers { is_typedef_declaration = 1; $$ = create_node("DeclarationSpecifiers", NULL, 2, $1, $2); }
    | type_specifier_node declaration_specifiers { is_typedef_declaration = 0; $$ = create_node("DeclarationSpecifiers", NULL, 2, $1, $2); }
    | type_qualifier declaration_specifiers { $$ = create_node("DeclarationSpecifiers", NULL, 2, $1, $2); }
    ;

storage_class_specifier
    : KEYWORD_TYPEDEF { $$ = create_node("StorageClassSpecifier", "typedef", 0); }
    ;

type_specifier
    : KEYWORD_VOID   { $$ = $1; }
    | KEYWORD_CHAR   { $$ = $1; }
    | KEYWORD_SHORT  { $$ = $1; }
    | KEYWORD_INT    { $$ = $1; }
    | KEYWORD_LONG   { $$ = $1; }
    | KEYWORD_FLOAT  { $$ = $1; }
    | KEYWORD_DOUBLE { $$ = $1; }
    | KEYWORD_SIGNED { $$ = $1; }
    | KEYWORD_UNSIGNED { $$ = $1; }
    ;

type_specifier_node
    : type_specifier { $$ = create_node("TypeSpecifier", $1, 0); }
    | TYPENAME { $$ = create_node("TypeName", $1, 0); }
    | struct_or_union_specifier { $$ = $1; }
    | enum_specifier { $$ = $1; }
    ;

init_declarator_list
    : init_declarator { $$ = create_node("InitDeclaratorList", NULL, 1, $1); }
    | init_declarator_list ',' init_declarator { $$ = create_node("InitDeclaratorList", NULL, 2, $3, $1); }
    ;

init_declarator
    : declarator {
        // Simply pass the declarator up. Insertion is handled in the 'declaration' rule.
        $$ = $1;
    }
    | declarator '=' initializer { $$ = create_node("InitDeclarator", "=", 2, $1, $3); }
    ;

declarator
    : pointer direct_declarator { $$ = create_node("PointerDeclarator", NULL, 2, $1, $2); }
    | direct_declarator { $$ = $1; }
    ;
 
type_name
    : specifier_qualifier_list { $$ = create_node("TypeName", NULL, 1, $1); }
    | specifier_qualifier_list abstract_declarator { $$ = create_node("TypeName", NULL, 2, $1, $2); }
    ;

abstract_declarator
    : pointer { $$ = $1; }
    | direct_abstract_declarator { $$ = $1; }
    | pointer direct_abstract_declarator { $$ = create_node("PointerAbstractDeclarator", NULL, 2, $1, $2); }
    ;

direct_abstract_declarator
    : '(' abstract_declarator ')' { $$ = create_node("ParenthesizedAbstractDeclarator", NULL, 1, $2); }
    | direct_abstract_declarator '[' assignment_expression_opt ']' { $$ = create_node("AbstractArraySuffix", NULL, 2, $1, $3); }
    | '[' assignment_expression_opt ']' { $$ = create_node("AbstractArraySuffix", NULL, 1, $2); } // Base case for array suffix
    | direct_abstract_declarator '(' parameter_type_list_opt ')' { $$ = create_node("AbstractFunctionSuffix", NULL, 2, $1, $3); }
    | '(' parameter_type_list_opt ')' { $$ = create_node("AbstractFunctionSuffix", NULL, 1, $2); } // Base case for function suffix
    ;

assignment_expression_opt
    : assignment_expression { $$ = $1; }
    | /* empty */ { $$ = create_node("EmptyExpression", NULL, 0); }
    ;

parameter_type_list_opt
    : parameter_type_list { $$ = $1; }
    | /* empty */ { $$ = create_node("EmptyParameterList", NULL, 0); }
    ;

/*
 * Unary Expressions
 */
unary_expression
    : postfix_expression { $$ = $1; }
    | OP_INCREMENT unary_expression { $$ = create_node("PrefixIncrement", "++", 1, $2); }
    | OP_DECREMENT unary_expression { $$ = create_node("PrefixDecrement", "--", 1, $2); }
    | unary_operator cast_expression { $$ = create_node("UnaryOp", $1, 1, $2); }
    | KEYWORD_SIZEOF unary_expression { $$ = create_node("SizeofUnaryExpr", NULL, 1, $2); }
    | KEYWORD_SIZEOF '(' type_name ')' { $$ = create_node("SizeofTypeExpr", NULL, 1, $3); }
    ;


/*
 * Primary Expressions
 */

pointer
    : '*' { $$ = create_node("Pointer", "*", 0); }
    | '*' pointer { $$ = create_node("Pointer", "*", 1, $2); }
    ;

struct_or_union_specifier
    : struct_or_union IDENTIFIER '{' struct_declaration_list '}' 
        { $$ = create_node("StructSpecifier", $2, 2, $1, $4); }
    | struct_or_union '{' struct_declaration_list '}'
        { $$ = create_node("StructSpecifier", "anonymous", 2, $1, $3); }
    | struct_or_union IDENTIFIER
        { $$ = create_node("StructSpecifier", $2, 1, $1); }
    ;

struct_or_union
    : KEYWORD_STRUCT { $$ = create_node("StructToken", "struct", 0); }
    | KEYWORD_UNION  { $$ = create_node("UnionToken", "union", 0); }
    ;

struct_declaration_list
    : struct_declaration { $$ = create_node("StructDeclarationList", NULL, 1, $1); }
    | struct_declaration_list struct_declaration { $$ = create_node("StructDeclarationList", NULL, 2, $1, $2); }
    ;

struct_declaration
    : specifier_qualifier_list struct_declarator_list ';' { $$ = create_node("StructDeclaration", NULL, 2, $1, $2); }
    ;

specifier_qualifier_list
    : type_specifier_node { $$ = create_node("SpecifierQualifierList", NULL, 1, $1); }
    | type_qualifier { $$ = create_node("SpecifierQualifierList", NULL, 1, $1); }
    | type_specifier_node specifier_qualifier_list { $$ = create_node("SpecifierQualifierList", NULL, 2, $1, $2); }
    | type_qualifier specifier_qualifier_list { $$ = create_node("SpecifierQualifierList", NULL, 2, $1, $2); }
    ;

struct_declarator_list
    : struct_declarator { $$ = create_node("StructDeclaratorList", NULL, 1, $1); }
    | struct_declarator_list ',' struct_declarator { $$ = create_node("StructDeclaratorList", NULL, 2, $1, $3); }
    ;

struct_declarator
    : declarator { $$ = $1; }
    ;

type_qualifier
    : KEYWORD_CONST { $$ = create_node("TypeQualifier", "const", 0); }
    | KEYWORD_VOLATILE { $$ = create_node("TypeQualifier", "volatile", 0); }
    | KEYWORD_RESTRICT { $$ = create_node("TypeQualifier", "restrict", 0); }
    ;

enum_specifier
    : KEYWORD_ENUM IDENTIFIER '{' enumerator_list '}' { $$ = create_node("EnumSpecifier", $2, 1, $4); }
    | KEYWORD_ENUM '{' enumerator_list '}' { $$ = create_node("EnumSpecifier", "anonymous", 1, $3); }
    | KEYWORD_ENUM IDENTIFIER '{' enumerator_list ',' '}' { $$ = create_node("EnumSpecifier", $2, 1, $4); }
    | KEYWORD_ENUM '{' enumerator_list ',' '}' { $$ = create_node("EnumSpecifier", "anonymous", 1, $3); }
    | KEYWORD_ENUM IDENTIFIER { $$ = create_node("EnumSpecifier", $2, 0); }
    ;

enumerator_list
    : enumerator { $$ = create_node("EnumeratorList", NULL, 1, $1); }
    | enumerator_list ',' enumerator { $$ = create_node("EnumeratorList", NULL, 2, $1, $3); }
    ;

enumerator
    : IDENTIFIER { $$ = create_node("Enumerator", $1, 0); }
    | IDENTIFIER '=' conditional_expression { $$ = create_node("Enumerator", $1, 1, $3); }
    ;

initializer
    : assignment_expression { $$ = $1; }
    | '{' initializer_list '}' { $$ = create_node("InitializerList", NULL, 1, $2); }
    ;

initializer_list
    : assignment_expression { $$ = create_node("InitValues", NULL, 1, $1); }
    | initializer_list ',' assignment_expression { $$ = create_node("InitValues", NULL, 2, $1, $3); }
    ;

direct_declarator
    : IDENTIFIER { $$ = create_node("Identifier", $1, 0); }
    | '(' declarator ')' { $$ = $2; }
    | direct_declarator '(' parameter_type_list ')' { $$ = create_node("FunctionDeclarator", NULL, 2, $1, $3); }
    | direct_declarator '(' ')' { $$ = create_node("FunctionDeclarator", "()", 1, $1); }
    | direct_declarator '[' assignment_expression ']' { $$ = create_node("ArrayDeclarator", NULL, 2, $1, $3); }
    | direct_declarator '[' ']' { $$ = create_node("ArrayDeclarator", "unspecified_size", 1, $1); }
    ;

parameter_type_list
    : parameter_list { $$ = $1; }
    ;

parameter_list
    : parameter_declaration { $$ = create_node("ParameterList", NULL, 1, $1); }
    | parameter_list ',' parameter_declaration { $$ = create_node("ParameterList", NULL, 2, $1, $3); }
    ;

parameter_declaration
    : declaration_specifiers declarator { $$ = create_node("ParameterDeclaration", NULL, 2, $1, $2); }
    | declaration_specifiers { $$ = create_node("ParameterDeclaration", NULL, 1, $1); } /* For void */
    ;

compound_statement
    : '{' '}' { 
        $$ = create_node("CompoundStatement", "{}", 0); 
      }
    | '{' block_item_list '}' { 
        $$ = create_node("CompoundStatement", NULL, 1, $2); 
      }
    ;

block_item_list
    : block_item { $$ = create_node("BlockItemList", NULL, 1, $1); }
    | block_item_list block_item { $$ =  $2; }
    ;

block_item
    : declaration { $$ = $1; }
    | statement   { $$ = $1; }
    ;

statement
    : expression_statement { $$ = $1; }
    | compound_statement   { $$ = $1; }
    | selection_statement  { $$ = $1; } 
    | iteration_statement  { $$ = $1; }
    | jump_statement       { $$ = $1; }
    | labeled_statement    { $$ = $1; }
    ;

expression_statement
    : ';' { $$ = create_node("EmptyStatement", ";", 0); }
    | expression ';' { $$ = create_node("ExpressionStatement", NULL, 1, $1); }
    ;

expression_opt
    : expression { $$ = $1; }
    | /* empty */ { $$ = create_node("EmptyExpression", NULL, 0); }
    ;

iteration_statement
    : KEYWORD_WHILE '(' expression ')' statement { $$ = create_node("WhileStatement", NULL, 2, $3, $5); }
    | KEYWORD_DO statement KEYWORD_WHILE '(' expression ')' ';' { $$ = create_node("DoWhileStatement", NULL, 2, $2, $5); }
    | KEYWORD_FOR '(' expression_opt ';' expression_opt ';' expression_opt ')' statement { $$ = create_node("ForStatement", NULL, 4, $3, $5, $7, $9); }
    | KEYWORD_FOR '(' declaration expression_opt ';' expression_opt ')' statement { $$ = create_node("ForDeclStatement", NULL, 4, $3, $4, $6, $8); }
    ;

selection_statement
    : KEYWORD_IF '(' expression ')' statement  { $$ = create_node("IfStatement", NULL, 2, $3, $5); }
    | KEYWORD_IF '(' expression ')' statement KEYWORD_ELSE statement { $$ = create_node("IfElseStatement", NULL, 3, $3, $5, $7); }
    | KEYWORD_SWITCH '(' expression ')' statement { $$ = create_node("SwitchStatement", NULL, 2, $3, $5); }
    ;

labeled_statement
    : IDENTIFIER ':' statement { $$ = create_node("LabeledStatement", $1, 1, $3); }
    | KEYWORD_CASE conditional_expression ':' statement { $$ = create_node("CaseStatement", NULL, 2, $2, $4); }
    | KEYWORD_DEFAULT ':' statement { $$ = create_node("DefaultStatement", NULL, 1, $3); }
    ;

jump_statement
    : KEYWORD_RETURN ';' { $$ = create_node("Return", NULL, 0); }
    | KEYWORD_RETURN expression ';' { $$ = create_node("Return", NULL, 1, $2); }
    | KEYWORD_BREAK ';' { $$ = create_node("BreakStatement", NULL, 0); }
    | KEYWORD_CONTINUE ';' { $$ = create_node("ContinueStatement", NULL, 0); }
    ;

expression
    : assignment_expression { $$ = $1; }
    | expression ',' assignment_expression { $$ = create_node("BinaryOp", ",", 2, $1, $3); }
    ;

assignment_expression
    : conditional_expression { $$ = $1; }
    | unary_expression assignment_operator assignment_expression { $$ = create_node("Assignment", $2, 2, $1, $3); }
    ;

assignment_operator
    : '=' { $$ = "="; } | OP_MUL_ASSIGN { $$ = "*="; } | OP_DIV_ASSIGN { $$ = "/="; }
    | OP_MOD_ASSIGN { $$ = "%="; } | OP_ADD_ASSIGN { $$ = "+="; } | OP_SUB_ASSIGN { $$ = "-="; }
    ;

conditional_expression
    : logical_or_expression { $$ = $1; }
    ;

logical_or_expression
    : logical_and_expression { $$ = $1; }
    | logical_or_expression OP_OR logical_and_expression { $$ = create_node("BinaryOp", "||", 2, $1, $3); }
    ;

logical_and_expression
    : inclusive_or_expression { $$ = $1; }
    | logical_and_expression OP_AND inclusive_or_expression { $$ = create_node("BinaryOp", "&&", 2, $1, $3); }
    ;

inclusive_or_expression
    : exclusive_or_expression { $$ = $1; }
    | inclusive_or_expression '|' exclusive_or_expression { $$ = create_node("BinaryOp", "|", 2, $1, $3); }
    ;

exclusive_or_expression
    : and_expression { $$ = $1; }
    | exclusive_or_expression '^' and_expression { $$ = create_node("BinaryOp", "^", 2, $1, $3); }
    ;

and_expression
    : equality_expression { $$ = $1; }
    | and_expression '&' equality_expression { $$ = create_node("BinaryOp", "&", 2, $1, $3); }
    ;

equality_expression
    : relational_expression { $$ = $1; }
    | equality_expression OP_EQ relational_expression { $$ = create_node("BinaryOp", "==", 2, $1, $3); }
    | equality_expression OP_NE relational_expression { $$ = create_node("BinaryOp", "!=", 2, $1, $3); }
    ;

relational_expression
    : shift_expression { $$ = $1; }
    | relational_expression '<' shift_expression { $$ = create_node("BinaryOp", "<", 2, $1, $3); }
    | relational_expression '>' shift_expression { $$ = create_node("BinaryOp", ">", 2, $1, $3); }
    | relational_expression OP_LE shift_expression { $$ = create_node("BinaryOp", "<=", 2, $1, $3); }
    | relational_expression OP_GE shift_expression { $$ = create_node("BinaryOp", ">=", 2, $1, $3); }
    ;

shift_expression
    : additive_expression { $$ = $1; }
    | shift_expression OP_SHIFT_LEFT additive_expression { $$ = create_node("BinaryOp", "<<", 2, $1, $3); }
    | shift_expression OP_SHIFT_RIGHT additive_expression { $$ = create_node("BinaryOp", ">>", 2, $1, $3); }
    ;

additive_expression
    : multiplicative_expression { $$ = $1; }
    | additive_expression '+' multiplicative_expression { $$ = create_node("BinaryOp", "+", 2, $1, $3); }
    | additive_expression '-' multiplicative_expression { $$ = create_node("BinaryOp", "-", 2, $1, $3); }
    ;

multiplicative_expression
    : cast_expression { $$ = $1; }
    | multiplicative_expression '*' cast_expression { $$ = create_node("BinaryOp", "*", 2, $1, $3); }
    | multiplicative_expression '/' cast_expression { $$ = create_node("BinaryOp", "/", 2, $1, $3); }
    | multiplicative_expression '%' cast_expression { $$ = create_node("BinaryOp", "%", 2, $1, $3); }
    ;

cast_expression
    : unary_expression { $$ = $1; }
    ;

unary_operator
    : '&' { $$ = "&"; } | '*' { $$ = "*"; } | '+' { $$ = "+"; } | '-' { $$ = "-"; } | '~' { $$ = "~"; } | '!' { $$ = "!"; }
    ;

postfix_expression
    : primary_expression { $$ = $1; }
    | postfix_expression '(' ')' { $$ = create_node("FunctionCall", NULL, 1, $1); }
    | postfix_expression '(' argument_expression_list ')' { $$ = create_node("FunctionCall", NULL, 2, $1, $3); }
    | postfix_expression OP_INCREMENT { $$ = create_node("PostfixIncrement", "++", 1, $1); }
    | postfix_expression OP_DECREMENT { $$ = create_node("PostfixDecrement", "--", 1, $1); }
    | postfix_expression '[' expression ']' { $$ = create_node("ArrayAccess", NULL, 2, $1, $3); }
    ;

argument_expression_list
    : assignment_expression { $$ = create_node("ArgumentList", NULL, 1, $1); }
    | argument_expression_list ',' assignment_expression { $$ = create_node("ArgumentList", NULL, 2, $1, $3); }
    ;

primary_expression
    : IDENTIFIER { $$ = create_node("Identifier", $1, 0); }
    | INT_CONST { $$ = create_node("IntConstant", $1, 0); }
    | FLOAT_CONST { $$ = create_node("FloatConstant", $1, 0); }
    | CHAR_CONST { $$ = create_node("CharConstant", $1, 0); }
    | STRING_LITERAL { $$ = create_node("StringLiteral", $1, 0); }
    | '(' expression ')' { $$ = $2; }
    ;



%%

/* C Code Section */
#include <stdarg.h>


/**
 * @brief Extracts the base type name from a declaration_specifiers AST node.
 * This is a simplified implementation and assumes the first type specifier is the primary one.
 * e.g., "unsigned int" will return "int". A more robust implementation would combine them.
 */
Type* get_base_type_from_specifiers(ASTNode* specifiers_node) {
    if (!specifiers_node) return create_base_type("int"); // Default to int

    // Traverse the list of specifiers to find a type specifier
    ASTNode* current = specifiers_node;
    while(current) {
        if (strcmp(current->node_type, "TypeSpecifier") == 0) {
            return create_base_type(current->value);
        }
        // If it's a list, check the first child, then move to the next
        if (current->num_children > 0) {
             if (strcmp(current->children[0]->node_type, "TypeSpecifier") == 0) {
                return create_base_type(current->children[0]->value);
            }
        }
        if (current->num_children > 1) {
            current = current->children[1];
        } else {
            break;
        }
    }
    return create_base_type("int"); // Default if no type found
}

/**
 * @brief Extracts the function name from a declarator AST node.
 */
char* get_declarator_name(ASTNode* declarator_node) {
    if (!declarator_node) return NULL;

    // Case 1: It's a simple identifier (e.g., "int x;")
    if (strcmp(declarator_node->node_type, "Identifier") == 0) {
        return strdup(declarator_node->value);
    }

    // Case 2: It's a function declarator (e.g., "int main(void)")
    if (strcmp(declarator_node->node_type, "FunctionDeclarator") == 0 && declarator_node->num_children > 0) {
        ASTNode* direct_declarator = declarator_node->children[0];
        if (strcmp(direct_declarator->node_type, "Identifier") == 0) {
            return strdup(direct_declarator->value);
        }
    }

    return NULL;
}

/**
 * @brief Recursively builds a complex type from a base type and a declarator AST node.
 * This handles pointers, arrays, and functions.
 */
Type* build_declarator_type(Type* base_type, ASTNode* declarator_node) {
    if (!declarator_node) return base_type;

    if (strcmp(declarator_node->node_type, "PointerDeclarator") == 0) {
        // This is a pointer. The base_type is what the pointer *points to*.
        // We need to find the innermost declarator to apply the base type,
        // then wrap it with pointer types on the way out.
        Type* inner_type = build_declarator_type(base_type, declarator_node->children[1]);
        
        // Now, wrap with pointer types for each '*' in the 'pointer' part of the AST.
        ASTNode* pointer_part = declarator_node->children[0];
        while (pointer_part) {
            inner_type = create_pointer_type(inner_type);
            pointer_part = (pointer_part->num_children > 0) ? pointer_part->children[0] : NULL;
        }
        return inner_type;
    }
    // Base case: we've reached the identifier. The type is just the base type.
    return base_type;
}

ASTNode* create_node(const char *node_type, const char *value, int num_children, ...) {
    ASTNode *node = (ASTNode*) malloc(sizeof(ASTNode));
    if (!node) {
        yyerror("Out of memory");
        exit(1);
    }
    node->node_type = strdup(node_type);
    node->value = value ? strdup(value) : NULL;
    node->num_children = num_children;
    if (num_children > 0) {
        node->children = (ASTNode**) malloc(num_children * sizeof(ASTNode*));
        va_list ap;
        va_start(ap, num_children);
        for (int i = 0; i < num_children; i++) {
            node->children[i] = va_arg(ap, ASTNode*);
        }
        va_end(ap);
    } else {
        node->children = NULL;
    }
    return node;
}

void print_ast(ASTNode *node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("%s", node->node_type);
    if (node->value) {
        printf(" (%s)", node->value);
    }
    printf("\n");

    for (int i = 0; i < node->num_children; i++) {
        print_ast(node->children[i], level + 1);
    }
}

void free_ast(ASTNode *node) {
    if (!node) return;
    for (int i = 0; i < node->num_children; i++) {
        free_ast(node->children[i]);
    }
    free(node->node_type);
    if (node->value) free(node->value);
    if (node->children) free(node->children);
    free(node);
}

void yyerror(const char *s) {
    fprintf(stderr, "Parse error on line %d near '%s': %s\n", line_count, yytext, s);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <sourcefile.c>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Cannot open input file");
        return 1;
    }

    yyin = file;
    init_symbol_table(); // Initialize the symbol table
    yyparse();
    fclose(file);

    if (ast_root) {
        printf("\n--- Abstract Syntax Tree ---\n");
        print_ast(ast_root, 0);
        printf("----------------------------\n");
        free_ast(ast_root);
    } else {
        printf("Parsing failed, no AST generated.\n");
    }
    print_symbol_table(); // Print symbol table contents

    return 0;
}