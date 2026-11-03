%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* For Windows compatibility, as unistd.h is not available */
#define YY_NO_UNISTD_H 1

// Define token names for printing
int line_count = 1;
int comment_start_line = 0;

char string_buffer[4096];
char *string_buffer_ptr;

// Symbol table implementation (simple linked list)
typedef struct Symbol {
    char *name;
    struct Symbol *next;
} Symbol;

Symbol *symbol_table_head = NULL;

void add_to_symbol_table(const char *name);
void print_symbol_table(void);

// Updated to print line numbers
void print_token(int line, const char *token_type, const char *text) {
    printf("L%-4d %-25s : %s\n", line, token_type, text);
}

void print_error(int line, const char *error_type, const char *text) {
    fprintf(stderr, "Error on line %d: %s %s\n", line, error_type, text);
}

int yywrap(void);
%}

%x IN_COMMENT
%x IN_STRING

/*Define regex for identifier */
ID      [a-zA-Z_][a-zA-Z0-9_]*

/* Integer constants (decimal, octal, hex) */
INT_CONST       0[xX][0-9a-fA-F]+|0[0-7]*|[1-9][0-9]*

/* Floating constants (simplified)*/
FLOAT_CONST     ([0-9]+\.[0-9]*([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+)

/* Character constants (simple)*/
CHAR_CONST      '\'([^\'\\]|\\.)\''

%%
"/*"         { comment_start_line = line_count; BEGIN(IN_COMMENT); }
<IN_COMMENT>{
"*/"       { BEGIN(INITIAL); }
\n         { line_count++; }
.          { /* Eat up comment characters */ }
<<EOF>>    { print_error(comment_start_line, "Unterminated multi-line comment starting on line", ""); exit(1); }
}

\"           { 
    string_buffer_ptr = string_buffer; 
    *string_buffer_ptr++ = '"'; /* Add opening quote */
    *string_buffer_ptr = '\0'; 
    BEGIN(IN_STRING); 
}
<IN_STRING>{
\"           { *string_buffer_ptr++ = '"'; /* Add closing quote */ *string_buffer_ptr = '\0'; print_token(line_count, "STRING_LITERAL", string_buffer); BEGIN(INITIAL); }
([^\\\"\n]+) { strcpy(string_buffer_ptr, yytext); string_buffer_ptr += yyleng; }
(\\\")      { strcpy(string_buffer_ptr, yytext); string_buffer_ptr += yyleng; }
(\\[^\"])   { strcpy(string_buffer_ptr, yytext); string_buffer_ptr += yyleng; }
\n          { print_error(line_count, "Unterminated string literal", ""); line_count++; BEGIN(INITIAL); }
<<EOF>>     { print_error(line_count, "Unterminated string literal at end of file", ""); exit(1); }
}
\n                   { line_count++; } // Increment line counter
[ \t\r]+             ;   // skip other whitespace
"//".*               { /* skip single line comment, but it might contain a \n at the end, which the next rule will catch */ }
"#".*                { /* skip preprocessor directives */ }  
"auto"               { print_token(line_count, "KEYWORD_AUTO", yytext); }
"break"              { print_token(line_count, "KEYWORD_BREAK", yytext); }
"case"               { print_token(line_count, "KEYWORD_CASE", yytext); }
"char"               { print_token(line_count, "KEYWORD_CHAR", yytext); }
"const"              { print_token(line_count, "KEYWORD_CONST", yytext); }
"continue"           { print_token(line_count, "KEYWORD_CONTINUE", yytext); }
"default"            { print_token(line_count, "KEYWORD_DEFAULT", yytext); }
"do"                 { print_token(line_count, "KEYWORD_DO", yytext); }
"double"             { print_token(line_count, "KEYWORD_DOUBLE", yytext); }
"else"               { print_token(line_count, "KEYWORD_ELSE", yytext); }
"enum"               { print_token(line_count, "KEYWORD_ENUM", yytext); }
"extern"             { print_token(line_count, "KEYWORD_EXTERN", yytext); }
"float"              { print_token(line_count, "KEYWORD_FLOAT", yytext); }
"for"                { print_token(line_count, "KEYWORD_FOR", yytext); }
"goto"               { print_token(line_count, "KEYWORD_GOTO", yytext); }
"if"                 { print_token(line_count, "KEYWORD_IF", yytext); }
"inline"             { print_token(line_count, "KEYWORD_INLINE", yytext); }
"int"                { print_token(line_count, "KEYWORD_INT", yytext); }
"long"               { print_token(line_count, "KEYWORD_LONG", yytext); }
"register"           { print_token(line_count, "KEYWORD_REGISTER", yytext); }
"restrict"           { print_token(line_count, "KEYWORD_RESTRICT", yytext); }
"return"             { print_token(line_count, "KEYWORD_RETURN", yytext); }
"short"              { print_token(line_count, "KEYWORD_SHORT", yytext); }
"signed"             { print_token(line_count, "KEYWORD_SIGNED", yytext); }
"sizeof"             { print_token(line_count, "KEYWORD_SIZEOF", yytext); }
"static"             { print_token(line_count, "KEYWORD_STATIC", yytext); }
"struct"             { print_token(line_count, "KEYWORD_STRUCT", yytext); }
"switch"             { print_token(line_count, "KEYWORD_SWITCH", yytext); }
"typedef"            { print_token(line_count, "KEYWORD_TYPEDEF", yytext); }
"union"              { print_token(line_count, "KEYWORD_UNION", yytext); }
"unsigned"           { print_token(line_count, "KEYWORD_UNSIGNED", yytext); }
"void"               { print_token(line_count, "KEYWORD_VOID", yytext); }
"volatile"           { print_token(line_count, "KEYWORD_VOLATILE", yytext); }
"while"              { print_token(line_count, "KEYWORD_WHILE", yytext); }
"_Bool"              { print_token(line_count, "KEYWORD_BOOL", yytext); }
"_Complex"           { print_token(line_count, "KEYWORD_COMPLEX", yytext); }
"_Imaginary"         { print_token(line_count, "KEYWORD_IMAGINARY", yytext); }


{ID}                 { 
                        print_token(line_count, "IDENTIFIER", yytext); 
                        add_to_symbol_table(yytext); 
                     }


{INT_CONST}          { print_token(line_count, "INT_CONST", yytext); }
{FLOAT_CONST}        { print_token(line_count, "FLOAT_CONST", yytext); }
{CHAR_CONST}         { print_token(line_count, "CHAR_CONST", yytext); }


"->"                 { print_token(line_count, "OP_ARROW", yytext); }
"++"                 { print_token(line_count, "OP_INCREMENT", yytext); }
"--"                 { print_token(line_count, "OP_DECREMENT", yytext); }
"<<"                 { print_token(line_count, "OP_SHIFT_LEFT", yytext); }
">>"                 { print_token(line_count, "OP_SHIFT_RIGHT", yytext); }
"<="                 { print_token(line_count, "OP_LE", yytext); }
">="                 { print_token(line_count, "OP_GE", yytext); }
"=="                 { print_token(line_count, "OP_EQ", yytext); }
"!="                 { print_token(line_count, "OP_NE", yytext); }
"&&"                 { print_token(line_count, "OP_AND", yytext); }
"||"                 { print_token(line_count, "OP_OR", yytext); }
"+="                 { print_token(line_count, "OP_ADD_ASSIGN", yytext); }
"-="                 { print_token(line_count, "OP_SUB_ASSIGN", yytext); }
"*="                 { print_token(line_count, "OP_MUL_ASSIGN", yytext); }
"/="                 { print_token(line_count, "OP_DIV_ASSIGN", yytext); }
"%="                 { print_token(line_count, "OP_MOD_ASSIGN", yytext); }
"&="                 { print_token(line_count, "OP_BITAND_ASSIGN", yytext); }
"^="                 { print_token(line_count, "OP_BITXOR_ASSIGN", yytext); }
"|="                 { print_token(line_count, "OP_BITOR_ASSIGN", yytext); }


"+"                  { print_token(line_count, "OP_PLUS", yytext); }
"-"                  { print_token(line_count, "OP_MINUS", yytext); }
"*"                  { print_token(line_count, "OP_MULTIPLY", yytext); }
"/"                  { print_token(line_count, "OP_DIVIDE", yytext); }
"%"                  { print_token(line_count, "OP_MODULO", yytext); }
"="                  { print_token(line_count, "OP_ASSIGN", yytext); }
"<"                  { print_token(line_count, "OP_LT", yytext); }
">"                  { print_token(line_count, "OP_GT", yytext); }
"&"                  { print_token(line_count, "OP_BITWISE_AND", yytext); }
"|"                  { print_token(line_count, "OP_BITWISE_OR", yytext); }
"^"                  { print_token(line_count, "OP_BITWISE_XOR", yytext); }
"~"                  { print_token(line_count, "OP_BITWISE_NOT", yytext); }
"!"                  { print_token(line_count, "OP_LOGICAL_NOT", yytext); }
"("                  { print_token(line_count, "PUNC_LPAREN", yytext); }
")"                  { print_token(line_count, "PUNC_RPAREN", yytext); }
"{"                  { print_token(line_count, "PUNC_LBRACE", yytext); }
"}"                  { print_token(line_count, "PUNC_RBRACE", yytext); }
"["                  { print_token(line_count, "PUNC_LBRACKET", yytext); }
"]"                  { print_token(line_count, "PUNC_RBRACKET", yytext); }
";"                  { print_token(line_count, "PUNC_SEMICOLON", yytext); }
","                  { print_token(line_count, "PUNC_COMMA", yytext); }
"."                  { print_token(line_count, "PUNC_DOT", yytext); }
"?"                  { print_token(line_count, "PUNC_QUESTION", yytext); }
":"                  { print_token(line_count, "PUNC_COLON", yytext); }


.                    { print_token(line_count, "UNKNOWN", yytext); }

%%

void add_to_symbol_table(const char *name) {
    Symbol *current = symbol_table_head;

    // Check if the symbol already exists to avoid duplicates
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return; // Already in the table
        }
        current = current->next;
    }

    // If not found, create a new symbol and add it to the head of the list
    Symbol *new_symbol = (Symbol *)malloc(sizeof(Symbol));
    if (!new_symbol) {
        perror("Failed to allocate memory for symbol");
        exit(1);
    }
    new_symbol->name = strdup(name); // Use strdup to safely copy the identifier
    new_symbol->next = symbol_table_head;
    symbol_table_head = new_symbol;
}

void print_symbol_table(void) {
    printf("\n--- Symbol Table (Unique Identifiers) ---\n");
    Symbol *current = symbol_table_head;
    while (current != NULL) {
        printf("  %s\n", current->name);
        current = current->next;
    }
    printf("-----------------------------------------\n");
}

int yywrap(void) {
    return 1; // Signal that there are no more files to process
}

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr,"Usage: %s <sourcefile.c>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if(!file) {
        perror("Cannot open input file");
        return 1;
    }

    // Set flex input to the file
    yyin = file;

    // Perform lexical analysis
    yylex();

    print_symbol_table();

    printf("\n----------------------------------\n");
    printf("Total lines processed: %d\n", line_count);
    fclose(file);
    return 0;
}
