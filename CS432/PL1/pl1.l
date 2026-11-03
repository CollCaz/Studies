%{
/*
 * Lexical analyzer for PL/I (based on the structure of the reference C lexer)
 *
 * Build:   flex pl1.l && gcc lex.yy.c -o pl1lex
 * Run:     ./pl1lex program.pl1
 *
 * Notes on PL/I that differ from C:
 *   - Case-insensitive (%option caseless; symbol table is normalised to UPPER).
 *   - Comments are only  slash-star ... star-slash  (no // comments, and they do not nest).
 *   - Strings use single quotes; a quote inside a string is doubled ('it''s').
 *   - String suffixes: B (bit), X (hex), BX, B1-B4, GX, G (graphic).
 *   - Numeric forms: fixed decimal (12, 3.14, .5), float decimal (1.5E10),
 *     binary (1011B), float binary (1.1E3B), complex/imaginary (5I, 1.5E2I).
 *   - '=' is both assignment and comparison, '||' is concatenation,
 *     '**' is exponentiation, '->' is the pointer qualifier.
 *   - NOT is  ¬  ^  ~   (so ¬= ^= ~= ¬< ¬> are "not equal/less/greater").
 *   - '%' starts a compile-time preprocessor statement (%INCLUDE, %IF ...).
 *   - PL/I has NO reserved words; keywords are recognised by lookup and are
 *     reported as keywords here, which is the usual convention for a coursework
 *     lexer.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int line_count = 1;
int comment_start_line = 0;
int error_count = 0;

/* ---------- symbol table (linked list, unique, case-folded) ---------- */
typedef struct Symbol {
    char *name;
    int   count;
    struct Symbol *next;
} Symbol;

Symbol *symbol_table_head = NULL;

void add_to_symbol_table(const char *name);
void print_token(int line, const char *token_type, const char *text);
void print_symbol_table(void);

/* ---------- keyword / built-in function tables ---------- */
static const char *keywords[] = {
    "ALLOCATE","ALLOC","AUTOMATIC","AUTO","BASED","BEGIN","BINARY","BIN","BIT",
    "BUFFERED","BY","BYNAME","BYVALUE","CALL","CASE","CHARACTER","CHAR","CLOSE",
    "COMPLEX","CPLX","CONDITION","CONTROLLED","CTL","DATA","DECIMAL","DEC",
    "DECLARE","DCL","DEFAULT","DFT","DEFINE","DEFINED","DEF","DELETE","DIMENSION",
    "DIM","DIRECT","DISPLAY","DO","EDIT","ELSE","END","ENTRY","ENVIRONMENT","ENV",
    "EXIT","EXTERNAL","EXT","FETCH","FILE","FIXED","FLOAT","FLUSH","FORMAT",
    "FREE","FROM","GENERIC","GET","GO","GOTO","IF","IGNORE","INITIAL","INIT",
    "INPUT","INTERNAL","INT","INTO","ITERATE","KEY","KEYED","KEYFROM","KEYTO",
    "LABEL","LEAVE","LIKE","LINE","LIST","LOCATE","NOT","OFFSET","ON","OPEN",
    "OPTIONS","OTHERWISE","OTHER","OUTPUT","PAGE","PICTURE","PIC","POINTER","PTR",
    "POSITION","POS","PRECISION","PREC","PRINT","PROCEDURE","PROC","READ",
    "RECORD","RECURSIVE","REFER","RELEASE","REORDER","REPEAT","REPLY","RESERVES",
    "RETURN","RETURNS","REVERT","REWRITE","SELECT","SET","SIGNAL","SIGNED",
    "SKIP","SNAP","STATIC","STOP","STREAM","STRING","SYSTEM","TASK","THEN","TITLE",
    "TO","UNALIGNED","UNAL","ALIGNED","UNBUFFERED","UNSIGNED","UNTIL","UPDATE",
    "VARIABLE","VARYING","VAR","VARYINGZ","WAIT","WHEN","WHILE","WRITE",
    "OVERFLOW","UNDERFLOW","ZERODIVIDE","FIXEDOVERFLOW","ERROR","ENDFILE",
    "ENDPAGE","CONVERSION","SIZE","SUBSCRIPTRANGE","STRINGRANGE","STRINGSIZE",
    NULL
};

static const char *builtins[] = {
    "ABS","ADDR","ATAN","ATAND","BOOL","CEIL","COS","COSD","COUNT","DATE",
    "DIVIDE","EXP","FLOOR","HBOUND","INDEX","LBOUND","LENGTH","LOG","LOG10",
    "LOG2","MAX","MIN","MOD","NULL","ONCODE","PLIRETV","REVERSE","ROUND",
    "SIGN","SIN","SIND","SQRT","SUBSTR","SUM","TAN","TAND","TIME","TRANSLATE",
    "TRIM","TRUNC","UNSPEC","VERIFY","FLOAT","CHARACTER","BIT","LOW","HIGH",
    "ADD","MULTIPLY","SUBTRACT","STRING","ALLOCATION","CURRENTSIZE","SIZE",
    NULL
};

static int in_table(const char **tbl, const char *s) {
    for (int i = 0; tbl[i]; i++)
        if (strcmp(tbl[i], s) == 0) return 1;
    return 0;
}

/* classify an identifier-shaped lexeme and print it */
static void handle_word(const char *text) {
    char up[256];
    size_t n = strlen(text);
    if (n >= sizeof up) n = sizeof up - 1;
    for (size_t i = 0; i < n; i++) up[i] = (char)toupper((unsigned char)text[i]);
    up[n] = '\0';

      if (in_table(keywords, up)) {
        char type[300];
        snprintf(type, sizeof type, "KEYWORD_%s", up);
        print_token(line_count, type, text);
    } else if (in_table(builtins, up)) {
        print_token(line_count, "BUILTIN_FUNCTION", text);
    } else {
        print_token(line_count, "IDENTIFIER", text);
        add_to_symbol_table(up);
    }
}

void print_token(int line, const char *token_type, const char *text) {
    printf("L%-4d %-25s : %s\n", line, token_type, text);
}

void print_error(int line, const char *error_type, const char *text) {
    error_count++;
    fprintf(stderr, "Error on line %d: %s %s\n", line, error_type, text);
}
%}

%option noyywrap
%option caseless
%option nounput noinput

%x IN_COMMENT

/* ---------------- definitions ---------------- */
/* Identifiers: letters, digits, _ $ @ # (first char not a digit) */
ID          [A-Za-z_$@#][A-Za-z0-9_$@#]*

D           [0-9]
/* fixed decimal: 12   3.14   5.   .5 */
FIXED_DEC   ({D}+\.?{D}*|\.{D}+)
/* float decimal: 1.5E10  2E-3 */
FLOAT_DEC   {FIXED_DEC}E[+-]?{D}+
/* binary: 1011B  1.01B */
BIN_FIXED   ([01]+\.?[01]*|\.[01]+)B
/* float binary: 1.1E3B */
BIN_FLOAT   ([01]+\.?[01]*|\.[01]+)E[+-]?{D}+B
/* imaginary (complex part): 5I  1.5E2I  101BI */
IMAG        ({BIN_FLOAT}|{BIN_FIXED}|{FLOAT_DEC}|{FIXED_DEC})I

/* character string: 'abc'  'it''s' (no newline inside) */
STR_BODY    '([^'\n]|'')*'
BAD_STR     '([^'\n]|'')*

%%

 /* ---------------- comments:  slash-star ... star-slash ---------------- */
"/*"                 { comment_start_line = line_count; BEGIN(IN_COMMENT); }
<IN_COMMENT>{
"*/"                 { BEGIN(INITIAL); }
\n                   { line_count++; }
[^*\n]+              { /* eat comment text */ }
"*"                  { /* lone star */ }
<<EOF>>              { print_error(comment_start_line,
                                   "Unterminated comment starting on line", "");
                       return 0; }
}

 /* ---------------- whitespace ---------------- */
\n                   { line_count++; }
[ \t\r\f]+           ;

 /* ---------------- preprocessor statements (%INCLUDE, %IF, ...) ---------------- */
"%"[ \t]*{ID}        { print_token(line_count, "PREPROCESSOR", yytext); }

 /* ---------------- strings ---------------- */
{STR_BODY}B[1-4]?    { print_token(line_count, "BIT_STRING_LITERAL", yytext); }
{STR_BODY}BX         { print_token(line_count, "BIT_STRING_LITERAL", yytext); }
{STR_BODY}X          { print_token(line_count, "HEX_STRING_LITERAL", yytext); }
{STR_BODY}GX         { print_token(line_count, "GRAPHIC_HEX_LITERAL", yytext); }
{STR_BODY}G          { print_token(line_count, "GRAPHIC_STRING_LITERAL", yytext); }
{STR_BODY}           { print_token(line_count, "STRING_LITERAL", yytext); }
{BAD_STR}/\n         { print_error(line_count, "Unterminated string literal:", yytext); }
{BAD_STR}            { print_error(line_count, "Unterminated string literal at end of file:", yytext); }

 /* ---------------- numbers (longest match picks the right kind) ---------------- */
{IMAG}               { print_token(line_count, "IMAGINARY_CONST", yytext); }
{BIN_FLOAT}          { print_token(line_count, "BINARY_FLOAT_CONST", yytext); }
{BIN_FIXED}          { print_token(line_count, "BINARY_FIXED_CONST", yytext); }
{FLOAT_DEC}          { print_token(line_count, "FLOAT_CONST", yytext); }
{FIXED_DEC}          { print_token(line_count, "FIXED_CONST", yytext); }

 /* ---------------- identifiers / keywords / built-ins ---------------- */
{ID}                 { handle_word(yytext); }

 /* ---------------- multi-character operators ---------------- */
"**"                 { print_token(line_count, "OP_EXPONENT", yytext); }
"||"|"!!"            { print_token(line_count, "OP_CONCAT", yytext); }
"->"                 { print_token(line_count, "OP_POINTER", yytext); }
"<="                 { print_token(line_count, "OP_LE", yytext); }
">="                 { print_token(line_count, "OP_GE", yytext); }
"¬="|"^="|"~="       { print_token(line_count, "OP_NE", yytext); }
"¬<"|"^<"|"~<"       { print_token(line_count, "OP_NOT_LT", yytext); }
"¬>"|"^>"|"~>"       { print_token(line_count, "OP_NOT_GT", yytext); }

 /* ---------------- single-character operators ---------------- */
"+"                  { print_token(line_count, "OP_PLUS", yytext); }
"-"                  { print_token(line_count, "OP_MINUS", yytext); }
"*"                  { print_token(line_count, "OP_MULTIPLY", yytext); }
"/"                  { print_token(line_count, "OP_DIVIDE", yytext); }
"="                  { print_token(line_count, "OP_EQUALS", yytext); }
"<"                  { print_token(line_count, "OP_LT", yytext); }
">"                  { print_token(line_count, "OP_GT", yytext); }
"&"                  { print_token(line_count, "OP_AND", yytext); }
"|"|"!"              { print_token(line_count, "OP_OR", yytext); }
"¬"|"^"|"~"          { print_token(line_count, "OP_NOT", yytext); }

 /* ---------------- punctuation ---------------- */
"("                  { print_token(line_count, "PUNC_LPAREN", yytext); }
")"                  { print_token(line_count, "PUNC_RPAREN", yytext); }
","                  { print_token(line_count, "PUNC_COMMA", yytext); }
";"                  { print_token(line_count, "PUNC_SEMICOLON", yytext); }
":"                  { print_token(line_count, "PUNC_COLON", yytext); }
"."                  { print_token(line_count, "PUNC_DOT", yytext); }

 /* ---------------- anything else ---------------- */
.                    { print_token(line_count, "UNKNOWN", yytext);
                       print_error(line_count, "Illegal character:", yytext); }

%%

void add_to_symbol_table(const char *name) {
    for (Symbol *cur = symbol_table_head; cur; cur = cur->next) {
        if (strcmp(cur->name, name) == 0) { cur->count++; return; }
    }
    Symbol *s = (Symbol *)malloc(sizeof(Symbol));
    if (!s) { perror("Failed to allocate memory for symbol"); exit(1); }
    s->name  = strdup(name);
    s->count = 1;
    s->next  = symbol_table_head;
    symbol_table_head = s;
}

void print_symbol_table(void) {
    printf("\n--- Symbol Table (Unique Identifiers) ---\n");
    for (Symbol *cur = symbol_table_head; cur; cur = cur->next)
        printf("  %-30s (used %d time%s)\n", cur->name, cur->count,
               cur->count == 1 ? "" : "s");
    printf("-----------------------------------------\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <sourcefile.pl1>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Cannot open input file");
        return 1;
    }
    yyin = file;

    yylex();

    print_symbol_table();
    printf("\n----------------------------------\n");
    printf("Total lines processed: %d\n", line_count);
    printf("Errors found: %d\n", error_count);
    fclose(file);
    return error_count ? 2 : 0;
}
