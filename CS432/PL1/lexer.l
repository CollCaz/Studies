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
ID      [a-zA-Z$#@_][a-zA-Z0-9$#@_]*

/* Integer constants (decimal, octal, hex) */
INT_CONST       0[xX][0-9a-fA-F]+|0[0-7]*|[1-9][0-9]*

/* Floating constants (simplified)*/
FLOAT_CONST     ([0-9]+\.[0-9]*([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+)

/* Character constants (simple)*/
CHAR_CONST      '\'([^\'\\]|\\.)\''

%{
/* ====================================================================
 * LEXER TODO LIST  (test file: lexer_test.pli)
 * ====================================================================
 *
 * --- Must fix (seen in latest output) ---
 * TODO: add char string rule, quote-doubling handled: '([^'\n]|'')*'
 * TODO: add bit string rule '...'B and hex string rule '...'X
 * TODO: add unterminated string error rule
 * TODO: verify fake comment inside a string (line 56) survives once strings match first
 * TODO: add leading-dot float rule (.5 currently lexes as PUNC_DOT + INT_CONST)
 * TODO: add binary constant rule (1010B, 11111111B)
 * TODO: add complex constant rule (4.0I, 2I)
 * TODO: add ^=, ^<, ^> and ^ rules to mirror the existing not-sign rules
 * TODO: add case-insensitive keyword table, emit KEYWORD instead of IDENTIFIER
 * TODO: add only non-keywords to the symbol table
 *
 * --- Cleanup ---
 * TODO: rename OP_BITWISE_AND / OP_BITWISE_OR to OP_AND / OP_OR
 * TODO: decide if built-ins (MAX, MOD, SUBSTR, LENGTH, TRIM, ABS) are keywords
 * TODO: decide if format items (A, F) are keywords
 * TODO: decide if 007 is INT_CONST or should be flagged
 *
 * --- Verify ---
 * TODO: re-run on lexer_test.pli, symbol table should hold only ~29 real names
 * TODO: check 'DEADBEEF'X and '00FF'X each give a single HEX_STRING token
 *
 * --- Error handling (uncomment invalid cases in test file one at a time) ---
 * TODO: unterminated string
 * TODO: unterminated comment
 * TODO: illegal characters (~ ` \ !)
 * TODO: malformed numbers (1.2.3, 12E, 1E+, 0xFF)
 * TODO: invalid bit string '1012'B and invalid hex string 'GHIJ'X
 * TODO: identifier starting with a digit (9LIVES)
 * TODO: errors report correct line number and lexing continues afterward
 *
 * --- Optional ---
 * TODO: report column numbers as well as line numbers
 * TODO: print token count summary by category
 * TODO: write expected-output files and diff against them automatically
 * ==================================================================== */
%}
%%
\n                   { line_count++; } // Increment line counter
[ \t\r]+             ;   // skip other whitespace

"/*"                 { comment_start_line = line_count; BEGIN(IN_COMMENT); }
<IN_COMMENT>{
"*/"                 { BEGIN(INITIAL); }
\n                   { line_count++; }
[^*\n]+              { /* eat comment text */ }
"*"                  { /* lone star that isn't followed by / */ }
<<EOF>>              { print_error(comment_start_line,
                                   "Unterminated comment starting on line", "");
                       return 0; }
}

\'           { 
    string_buffer_ptr = string_buffer; 
    *string_buffer_ptr++ = '\''; /* Add opening quote */
    *string_buffer_ptr = '\0'; 
    BEGIN(IN_STRING); 
}
<IN_STRING>{
\'           { *string_buffer_ptr++ = '\''; /* Add closing quote */ *string_buffer_ptr = '\0'; print_token(line_count, "STRING_LITERAL", string_buffer); BEGIN(INITIAL); }
([^\\\'\n]+) { strcpy(string_buffer_ptr, yytext); string_buffer_ptr += yyleng; }
\'\'         { strcpy(string_buffer_ptr, yytext); string_buffer_ptr += yyleng; }
(\\[^\'])   { strcpy(string_buffer_ptr, yytext); string_buffer_ptr += yyleng; }
\n          { print_error(line_count, "Unterminated string literal", ""); line_count++; BEGIN(INITIAL); }
<<EOF>>     { print_error(line_count, "Unterminated string literal at end of file", ""); exit(1); }
}


","                  { print_token(line_count, "PUNC_COMMA", yytext); }
"."                  { print_token(line_count, "PUNC_DOT", yytext); }
";"                  { print_token(line_count, "PUNC_SEMICOLON", yytext); }
":"                  { print_token(line_count, "PUNC_COLON", yytext); }
"("                  { print_token(line_count, "PUNC_LPAREN", yytext); }
")"                  { print_token(line_count, "PUNC_RPAREN", yytext); }
"%"                  { print_token(line_count, "PUNC_INDICATOR", yytext); }
"->"                 { print_token(line_count, "PUNC_LOCATOR", yytext); }
"=>"                 { print_token(line_count, "PUNC_LOCATOR", yytext); }


"+"                  { print_token(line_count, "OP_PLUS", yytext); }
"-"                  { print_token(line_count, "OP_MINUS", yytext); }
"**"                 { print_token(line_count, "OP_EXPONENTIATE", yytext); }
"*"                  { print_token(line_count, "OP_MULTIPLY", yytext); }
"/"                  { print_token(line_count, "OP_DIVIDE", yytext); }

"¬="                 { print_token(line_count, "OP_NE", yytext); }
"<>"                 { print_token(line_count, "OP_NE", yytext); }
"¬<"                 { print_token(line_count, "OP_NLT", yytext); }
"¬>"                 { print_token(line_count, "OP_NGT", yytext); }
"<="                 { print_token(line_count, "OP_LE", yytext); }
">="                 { print_token(line_count, "OP_GE", yytext); }
"="                  { print_token(line_count, "OP_ASSIGN", yytext); }
"<"                  { print_token(line_count, "OP_LT", yytext); }
">"                  { print_token(line_count, "OP_GT", yytext); }

"||"                 { print_token(line_count, "OP_STRING_CONCAT", yytext); }

"¬"                  { print_token(line_count, "OP_LOGICAL_NOT", yytext); }
"&"                  { print_token(line_count, "OP_BITWISE_AND", yytext); }
"|"                  { print_token(line_count, "OP_BITWISE_OR", yytext); }


{INT_CONST}          { print_token(line_count, "INT_CONST", yytext); }
{FLOAT_CONST}        { print_token(line_count, "FLOAT_CONST", yytext); }
{CHAR_CONST}         { print_token(line_count, "CHAR_CONST", yytext); }
{ID}                 { 
                        print_token(line_count, "IDENTIFIER", yytext); 
                        add_to_symbol_table(yytext); 
                     }


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

