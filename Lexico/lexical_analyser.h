#ifndef LEXICAL_ANALYSER
#define LEXICAL_ANALYSER

#include<stdio.h>
#include<iostream>
#include<string.h>

const int MAX_CONSTS = 500;


typedef enum{
// Reseverd words
ARRAY, BOOLEAN, BREAK, CHAR, CONTINUE, DO, ELSE, FALSE, FUNCTION, IF, INTEGER, OF, RETURN,STRING, STRUCT, TRUE, TYPE, VAR, WHILE,
// symbols
COLON, SEMI_COLON, COMMA, EQUALS, LEFT_SQUARE, RIGHT_SQUARE, LEFT_BRACES, RIGHT_BRACES, LEFT_PARENTHESIS, RIGHT_PARENTHESIS, AND, OR, LESS_THAN, GREATER_THAN, LESS_OR_EQUAL, GREATER_OR_EQUAL, NOT_EQUAL, EQUAL_EQUAL, PLUS, PLUS_PLUS, MINUS, MINUS_MINUS, TIMES, DIVIDE, DOT, NOT,
// regular tokens
CHARACTER, NUMERAL, STRINGVAL, IDT,
// token deconhecido
UNKNOWN,
// final de arquivo
ENDFILE
} t_token;

typedef struct { 
  int  type; // 0-char, 1-int, 2- string       
  union {
    char   cVal;
    int    nVal; 
    char * sVal;       
  } _; 
} t_const;

// global variable
extern t_const vConsts[MAX_CONSTS];
extern int nNumConsts;
extern char nextChar;
extern t_token token; 
extern int tokenSecundario;

// functions
t_token searchKeyWord( string name );
int searchName( string name );
int addCharConst(char c); 
int addIntConst(int n);
int addStringConst(string s);
char getCharConst(int n); 
int getIntConst(int n); 
char *getStringConst(int n);
char readChar(void);
t_token nextToken(void); 

#endif