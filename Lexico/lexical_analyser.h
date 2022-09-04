#ifndef LEXICAL_ANALYSER
#define LEXICAL_ANALYSER

#include<stdio.h>
#include<iostream>
#include<string.h>
#include<unordered_map>

using namespace std;

const int MAX_CONSTS = 500;
const int MAX_NUM_LEN = 10;


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

typedef struct T_CONST{ 
  public:
    int type; // 0-char, 1-int, 2- string       
    union {
      char cVal;
      int nVal; 
      char* sVal;       
    } _; 
} t_const;

// global variables
extern FILE *program_file;
extern t_const vConsts[MAX_CONSTS];
extern int nNumConsts;
extern char nextChar;
extern t_token token; 
extern int secondaryToken;
extern unordered_map<int, string> terminalNames;
extern unordered_map<string,t_token> t_tokenReservedWords;
extern unordered_map<string,int> secondatyTokenId;
extern string tokenString;


// functions
t_token searchKeyWord(string name); //OK
int searchName(string name); // OK
int addCharConst(char c); //OK
int addIntConst(int n); // ok
int addStringConst(char* s);// ok
char getCharConst(int n); // ok
int getIntConst(int n);   // ok
char *getStringConst(int n); // ok
char readChar(); //ok
t_token nextToken(); 

#endif