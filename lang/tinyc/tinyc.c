/*
 This is a compiler for the Tiny-C language based on Marc Feeley's
 compiler for the Tiny-C language available at:
 <http://www.iro.umontreal.ca/~felipe/IFT2030-Automne2002/Complements/tinyc.c>

 The implementation of this compiler differs a little (but not much)
 from Feeley's implementation. However, it supports the same grammar
 as that of Feely's Tiny-C language.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Grammar:

<program> ::= <statement>
<statement> ::= "if" <paren_expr> <statement> |
                "if" <paren_expr> <statement> "else" <statement> |
                "while" <paren_expr> <statement> |
                "do" <statement> "while" <paren_expr> ";" |
                "{" { <statement> } "}" |
                <expr> ";" |
                ";"
<paren_expr> ::= "(" <expr> ")"
<expr> ::= <test> | <id> "=" <expr>
<test> ::= <sum> | <sum> "<" <sum>
<sum> ::= <term> | <sum> "+" <term> | <sum> "-" <term>
<term> ::= <id> | <int> | <paren_expr>
<id> ::= "a" | "b" | "c" | "d" | ... | "z"
<int> ::= <unsigned decimal integer>
*/

/* Lexer. */
enum {
    T_DO,
    T_ELSE,
    T_IF,
    T_WHILE,
    T_LBRACE,
    T_RBRACE,
    T_LPAREN,
    T_RPAREN,
    T_PLUS,
    T_MINUS,
    T_LESS,
    T_SEMICOLON,
    T_EQUAL,
    T_INT,
    T_ID,
    T_END
};

char *token_str[] = {
    "T_DO",
    "T_ELSE",
    "T_IF",
    "T_WHILE",
    "T_LBRACE",
    "T_RBRACE",
    "T_LPAREN",
    "T_RPAREN",
    "T_PLUS",
    "T_MINUS",
    "T_LESS",
    "T_SEMICOLON",
    "T_EQUAL",
    "T_INT",
    "T_ID",
    "T_END"
};

char *keywords[] = {"do", "else", "if", "while", NULL};

int ch = ' ';
int token;
int val;
char word[6];

void error(char *msg)
{
    fprintf(stderr, "error: token %s, char '%c', %s\n",
            token_str[token], ch, msg);
    exit(1);
}

void next_char() {
    ch = getchar();
}

void next_token()
{
    while (ch == ' ' || ch == '\n') {
        next_char();
    }
    switch (ch) {
    case EOF:
        token = T_END;
        break;
    case '{':
        next_char();
        token = T_LBRACE;
        break;
    case '}':
        next_char();
        token = T_RBRACE;
        break;
    case '(':
        next_char();
        token = T_LPAREN;
        break;
    case ')':
        next_char();
        token = T_RPAREN;
        break;
    case '+':
        next_char();
        token = T_PLUS;
        break;
    case '-':
        next_char();
        token = T_MINUS;
        break;
    case '<':
        next_char();
        token = T_LESS;
        break;
    case ';':
        next_char();
        token = T_SEMICOLON;
        break;
    case '=':
        next_char();
        token = T_EQUAL;
        break;
    default:
        if (ch >= '0' && ch <= '9') {
            /* Values greater than INT_MAX will cause overflow and
               invoke undefined behaviour. */
            val = 0;
            while (ch >= '0' && ch <= '9') {
                val = val * 10 + (ch - '0');
                next_char();
            }
            token = T_INT;
        } else if (ch >= 'a' && ch <= 'z') {
            int i = 0;
            while (ch >= 'a' && ch <= 'z') {
                word[i++] = ch;
                next_char();
                if (i == sizeof word) {
                    error("word too long");
                }
            }
            word[i] = '\0';
            token = 0;
            /* Check if word is a keyword. */
            while (keywords[token] != NULL &&
                   strcmp(keywords[token], word) != 0) {
                token++;
            }
            if (keywords[token] == NULL) {
                if (word[1] == '\0') {
                    token = T_ID;
                } else {
                    error("variable name must be a single letter");
                }
            }
        } else {
            error("unexpected character");
        }
    }
}

/* Parser. */
enum {
    N_VAR,
    N_INT,
    N_ADD,
    N_SUB,
    N_LT,
    N_SET,
    N_IF,
    N_IFELSE,
    N_WHILE,
    N_DO,
    N_SEQ,
    N_EXPR,
    N_PROG
};

char *node_type_str[] = {
    "N_VAR",
    "N_INT",
    "N_ADD",
    "N_SUB",
    "N_LT",
    "N_SET",
    "N_IF",
    "N_IFELSE",
    "N_WHILE",
    "N_DO",
    "N_SEQ",
    "N_EXPR",
    "N_PROG"
};

struct node {
    int type;
    int val;
    struct node *o1;
    struct node *o2;
    struct node *o3;
};

struct node *new_node(int type)
{
    struct node *x = malloc(sizeof (struct node));
    x->type = type;
    x->val = 0;
    x->o1 = x->o2 = x->o3 = NULL;
    return x;
}

struct node *paren_expr();

/* <term> ::= <id> | <int> | <paren_expr> */
struct node *term()
{
    struct node *x;
    if (token == T_ID) {
        x = new_node(N_VAR);
        x->val = word[0] - 'a';
        next_token();
    } else if (token == T_INT) {
        x = new_node(N_INT);
        x->val = val;
        next_token();
    } else {
        x = paren_expr();
    }
    return x;
}

/* <sum> ::= <term> | <sum> "+" <term> | <sum> "-" <term> */
struct node *sum()
{
    struct node *t;
    struct node *x = term();
    while (token == T_PLUS || token == T_MINUS) {
        t = x;
        x = new_node(token == T_PLUS ? N_ADD : N_SUB);
        next_token();
        x->o1 = t;
        x->o2 = term();
    }
    return x;
}

/* <test> ::= <sum> | <sum> "<" <sum> */
struct node *test()
{
    struct node *t;
    struct node *x = sum();
    if (token == T_LESS) {
        t = x;
        x = new_node(N_LT);
        next_token();
        x->o1 = t;
        x->o2 = sum();
    }
    return x;
}

/* <expr> ::= <test> | <id> "=" <expr> */
struct node *expr()
{
    struct node *t;
    struct node *x = test();
    if (x->type == N_VAR && token == T_EQUAL) {
        t = x;
        x = new_node(N_SET);
        next_token();
        x->o1 = t;
        x->o2 = expr();
    }
    return x;
}

/* <paren_expr> ::= "(" <expr> ")" */
struct node *paren_expr()
{
    struct node *x;
    if (token == T_LPAREN) {
        next_token();
    } else {
        error("expected lparen");
    }
    x = expr();
    if (token == T_RPAREN) {
        next_token();
    } else {
        error("expected rparen");
    }
    return x;
}

struct node *statement()
{
    struct node *t;
    struct node *x;
    if (token == T_IF) {
        /* "if" <paren_expr> <statement> */
        x = new_node(N_IF);
        next_token();
        x->o1 = paren_expr();
        x->o2 = statement();
        if (token == T_ELSE) {
            /* ... "else" <statement> */
            x->type = N_IFELSE;
            next_token();
            x->o3 = statement();
        }

    } else if (token == T_WHILE) {
        /* "while" <paren_expr> <statement> */
        x = new_node(N_WHILE);
        next_token();
        x->o1 = paren_expr();
        x->o2 = statement();
    } else if (token == T_DO) {
        /* "do" <statement> "while" <paren_expr> ";" */
        x = new_node(N_DO);
        next_token();
        x->o1 = statement();
        if (token == T_WHILE) {
            next_token();
        } else {
            error("expected while");
        }
        x->o2 = paren_expr();
        if (token == T_SEMICOLON) {
            next_token();
        } else {
            error("expected semi");
        }
    } else if (token == T_LBRACE) {
        /* "{" <statement> "}" */
        next_token();
        while (token != T_RBRACE) {
            t = x;
            x = new_node(N_SEQ);
            x->o1 = t;
            x->o2 = statement();
        }
        next_token();
    } else {
        /* <expr> ";" */
        x = new_node(N_EXPR);
        x->o1 = expr();
        if (token == T_SEMICOLON) {
            next_token();
        } else {
            error("expected semi");
        }
    }
    return x;
}

struct node *program()
{
    struct node *x = new_node(N_PROG);
    next_token();
    x->o1 = statement();
    if (token != T_END) {
        error("expected end of input");
    }
    return x;
}

void indent(int level) {
    int i;
    for (i = 0; i < 2 * level; i++) {
        putchar(' ');
    }
}

void print_tree(struct node *x, int level) {
    indent(level);
    printf("%s [%d]\n", node_type_str[x->type], x->val);
    if (x->o1) {
        print_tree(x->o1, level + 1);
    }
    if (x->o2) {
        print_tree(x->o2, level + 1);
    }
    if (x->o3) {
        print_tree(x->o3, level + 1);
    }
}

/* Code generator. */
enum {
    I_FETCH,
    I_STORE,
    I_PUSH,
    I_POP,
    I_ADD,
    I_SUB,
    I_LT,
    I_JZ,
    I_JNZ,
    I_JMP,
    I_HALT
};

char *code_str[] = {
    "I_FETCH",
    "I_STORE",
    "I_PUSH",
    "I_POP",
    "I_ADD",
    "I_SUB",
    "I_LT",
    "I_JZ",
    "I_JNZ",
    "I_JMP",
    "I_HALT"
};

char object[1000];
char *here = object;

void gen(char c) {
    *here++ = c;
}

void *hole() {
    return here++;
}

void fix(char *src, char *dst) {
    *src = dst - src;
}

void compile(struct node *x) {
    char *p;
    char *q;
    switch (x->type) {
    case N_VAR:
        gen(I_FETCH);
        gen(x->val);
        break;
    case N_INT:
        gen(I_PUSH);
        gen(x->val);
        break;
    case N_ADD:
        compile(x->o1);
        compile(x->o2);
        gen(I_ADD);
        break;
    case N_SUB:
        compile(x->o1);
        compile(x->o2);
        gen(I_SUB);
        break;
    case N_LT:
        compile(x->o1);
        compile(x->o2);
        gen(I_LT);
        break;
    case N_SET:
        compile(x->o2);
        gen(I_STORE);
        gen(x->o1->val);
        break;
    case N_IF:
        compile(x->o1);
        gen(I_JZ);
        p = hole();
        compile(x->o2);
        fix(p, here);
        break;
    case N_IFELSE:
        compile(x->o1);
        gen(I_JZ);
        p = hole();
        compile(x->o2);
        gen(I_JMP);
        q = hole();
        fix(p, here);
        compile(x->o3);
        fix(q, here);
        break;
    case N_WHILE:
        p = here;
        compile(x->o1);
        gen(I_JZ);
        q = hole();
        compile(x->o2);
        gen(I_JMP);
        fix(hole(), p);
        fix(q, here);
        break;
    case N_DO:
        p = here;
        compile(x->o1);
        compile(x->o2);
        gen(I_JNZ);
        fix(hole(), p);
        break;
    case N_SEQ:
        compile(x->o1);
        compile(x->o2);
        break;
    case N_EXPR:
        compile(x->o1);
        gen(I_POP);
        break;
    case N_PROG:
        compile(x->o1);
        gen(I_HALT);
        break;
    }
}

void print_object()
{
    char *pc = object;
    while (1) {
        switch (*pc++) {
        case I_FETCH:
            printf("I_FETCH %d\n", *pc++);
            break;
        case I_STORE:
            printf("I_STORE %d\n", *pc++);
            break;
        case I_PUSH:
            printf("I_PUSH %d\n", *pc++);
            break;
        case I_POP:
            printf("I_POP\n");
            break;
        case I_ADD:
            printf("I_ADD\n");
            break;
        case I_SUB:
            printf("I_SUB\n");
            break;
        case I_LT:
            printf("I_LT\n");
            break;
        case I_JMP:
            printf("I_JMP %d\n", *pc++);
            break;
        case I_JZ:
            printf("I_JZ %d\n", *pc++);
            break;
        case I_JNZ:
            printf("I_JNZ %d\n", *pc++);
            break;
        case I_HALT:
            printf("I_HALT\n");
            return;
        }
    }
}

/* VM */
int globals[26];

void run()
{
    int stack[1000];
    int *sp = stack;
    char *pc = object;
    while (1) {
        switch (*pc++) {
        case I_FETCH:
            *sp++ = globals[(int) *pc++];
            break;
        case I_STORE:
            globals[(int) *pc++] = sp[-1];
            break;
        case I_PUSH:
            *sp++ = *pc++;
            break;
        case I_POP:
            sp--;
            break;
        case I_ADD:
            sp[-2] = sp[-2] + sp[-1];
            sp--;
            break;
        case I_SUB:
            sp[-2] = sp[-2] - sp[-1];
            sp--;
            break;
        case I_LT:
            sp[-2] = sp[-2] < sp[-1];
            sp--;
            break;
        case I_JMP:
            pc += *pc;
            break;
        case I_JZ:
            if (sp[-1] == 0) {
                pc += *pc;
            } else {
                pc++;
            }
            sp--;
            break;
        case I_JNZ:
            if (sp[-1] != 0) {
                pc += *pc;
            } else {
                pc++;
            }
            sp--;
            break;
        default:
            return;
        }
    }
}

int main()
{
    int i;
    struct node *x;

    x = program();
    print_tree(x, 0);

    compile(x);
    print_object();

    for (i = 0; i < 26; i++) {
        globals[i] = 0;
    }

    run();

    for (i = 0; i < 26; i++) {
        if (globals[i] != 0) {
            printf("%c = %d\n", 'a' + i, globals[i]);
        }
    }
}
