#include "lexical_analyser.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

t_const vConsts[MAX_CONSTS];
int nNumConsts = 0;
char nextChar = '\x20';  // '\x20' represents the space character
t_token token = UNKNOWN; 
int secondaryToken = 0;
string tokenString = "";
unordered_map<int, string> terminalNames;
unordered_map<string,t_token> t_tokenMap;
unordered_map<string,int> secondatyTokenId;

void setTerminalNames(){
  terminalNames[ARRAY] = "ARRAY";
  terminalNames[BOOLEAN] = "BOOLEAN";
  terminalNames[BREAK] = "BREAK";
  terminalNames[CHAR] = "CHAR";
  terminalNames[CONTINUE] = "CONTINUE";
  terminalNames[DO] = "DO";
  terminalNames[ELSE] = "ELSE";
  terminalNames[FALSE] = "FALSE";
  terminalNames[FUNCTION] = "FUNCTION";
  terminalNames[IF] = "IF";
  terminalNames[INTEGER] = "INTEGER";
  terminalNames[OF] = "OF";
  terminalNames[RETURN] = "RETURN";
  terminalNames[STRING] = "STRING";
  terminalNames[STRUCT] = "STRUCT";
  terminalNames[TRUE] = "TRUE";
  terminalNames[TYPE] = "TYPE";
  terminalNames[VAR] = "VAR";
  terminalNames[WHILE] = "WHILE";
  terminalNames[COLON] = "COLON";
  terminalNames[SEMI_COLON] = "SEMI_COLON";
  terminalNames[COMMA] = "COMMA";
  terminalNames[EQUALS] = "EQUALS";
  terminalNames[LEFT_SQUARE] = "LEFT_SQUARE";
  terminalNames[RIGHT_SQUARE] = "RIGHT_SQUARE";
  terminalNames[LEFT_BRACES] = "LEFT_BRACES";
  terminalNames[RIGHT_BRACES] = "RIGHT_BRACES";
  terminalNames[LEFT_PARENTHESIS] = "LEFT_PARENTHESIS";
  terminalNames[RIGHT_PARENTHESIS] = "RIGHT_PARENTHESIS";
  terminalNames[AND] = "AND";
  terminalNames[OR] = "OR";
  terminalNames[LESS_THAN] = "LESS_THAN";
  terminalNames[GREATER_THAN] = "GREATER_THAN";
  terminalNames[LESS_OR_EQUAL] = "LESS_OR_EQUAL";
  terminalNames[GREATER_OR_EQUAL] = "GREATER_OR_EQUAL";
  terminalNames[NOT_EQUAL] = "NOT_EQUAL";
  terminalNames[EQUAL_EQUAL] = "EQUAL_EQUAL";
  terminalNames[PLUS] = "PLUS";
  terminalNames[PLUS_PLUS] = "PLUS_PLUS";
  terminalNames[MINUS] = "MINUS";
  terminalNames[MINUS_MINUS] = "MINUS_MINUS";
  terminalNames[TIMES] = "TIMES";
  terminalNames[DIVIDE] = "DIVIDE";
  terminalNames[DOT] = "DOT";
  terminalNames[NOT] = "NOT";
  terminalNames[CHARACTER] = "CHARACTER";
  terminalNames[NUMERAL] = "NUMERAL";
  terminalNames[STRINGVAL] = "STRINGVAL";
  terminalNames[IDT] = "IDT";
  terminalNames[UNKNOWN] = "UNKNOWN";
}

void setTokenMap(){
  t_tokenMap["array"] = ARRAY;
  t_tokenMap["boolean"] = BOOLEAN;
  t_tokenMap["break"] = BREAK;
  t_tokenMap["char"] = CHAR;
  t_tokenMap["continue"] = CONTINUE;
  t_tokenMap["do"] = DO;
  t_tokenMap["else"] = ELSE;
  t_tokenMap["false"] = FALSE;
  t_tokenMap["function"] = FUNCTION;
  t_tokenMap["if"] = IF;
  t_tokenMap["integer"] = INTEGER;
  t_tokenMap["of"] = OF;
  t_tokenMap["return"] = RETURN;
  t_tokenMap["string"] = STRING;
  t_tokenMap["struct"] = STRUCT;
  t_tokenMap["true"] = TRUE;
  t_tokenMap["type"] = TYPE;
  t_tokenMap["var"] = VAR;
  t_tokenMap["while"] = WHILE;
}



