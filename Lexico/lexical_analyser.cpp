#include "lexical_analyser.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

FILE *program_file;
t_const vConsts[MAX_CONSTS];
int nNumConsts = 0;
char nextChar = '\x20';  // '\x20' represents the space character
t_token token = UNKNOWN; 
int secondaryToken = 0;
string tokenString = "";
unordered_map<int, string> terminalNames;
unordered_map<string,t_token> t_tokenMap;
unordered_map<string,int> secondatyTokenId;
int line = 1;

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
  setTerminalNames();
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

t_token searchKeyWord(string name){ //
  setTokenMap();
  return t_tokenMap.count(name) == 1 ? t_tokenMap[name] : IDT;
}

int searchName(string name){
    static int secondaryCounter = 0;
    if(secondatyTokenId.count(name) == 1){
      return secondatyTokenId[name];
    }
    secondatyTokenId[name] = secondaryCounter;
    return secondaryCounter++;
}

int addCharConst(char c){
	t_const _const;
	_const._.cVal = c;
	vConsts[nNumConsts] = _const;
	return nNumConsts++;
}

int addIntConst(int n){
  t_const _const;
	_const._.nVal = n;
	vConsts[nNumConsts] = _const;
	return nNumConsts++;
}

int addStringConst(char* s){
  t_const _const;
  _const._.sVal = s;
	vConsts[nNumConsts] = _const;
	return nNumConsts++;
}

char getCharConst(int n){
  return vConsts[n]._.cVal;
}

int getIntConst(int n){
  return vConsts[n]._.nVal;
}

char* getStringConst(int n){
	return vConsts[n]._.sVal;
}

char readChar(){
	char c =  fgetc(program_file);
  // cout << c << endl;
  line++;
  return c;
}

t_token nextToken(){
  tokenString = "";
  // hasSecondaryToken = false;
  while(isspace(nextChar)) nextChar = readChar();

  if(nextChar == EOF){
    token = ENDFILE;
    return token;
  }

  if(isalpha(nextChar)){
    while(isalnum(nextChar) || nextChar == '_'){
      tokenString += nextChar;
      nextChar = readChar();
    }
    token = searchKeyWord(tokenString);
    // cout << "Read:" << tokenString << ", Token: " << token << endl;
    
    if(token == IDT){
      secondaryToken = searchName(tokenString);
      // hasSecondaryToken = true;
      // cout << ", Token Secundario IDT " << secondaryToken << endl;

    }
  } 
  else if(isdigit(nextChar)){ // only working with integer numbers not floating pointers
    char number[MAX_NUM_LEN+1];
    int i=0;

    while(isdigit(nextChar)){
      tokenString += nextChar;
      number[i] = nextChar;
      i++;
      nextChar = readChar();
    }
    // cout << "Read:" << tokenString << ", Token: " << token << endl;


    number[i] = '\0';
    token = NUMERAL;
    secondaryToken = addIntConst(atoi(number));
    // hasSecondaryToken = true;
  } 
  else if(nextChar == '"'){
    nextChar = readChar();

    while(nextChar != '"'){
      tokenString += nextChar;
      nextChar = readChar();
    }
    // cout << "Read:" << tokenString << ", Token: " << token << endl;


    token = STRINGVAL;
    char* constString = new char[tokenString.size() + 1];
    memcpy(constString, tokenString.c_str(), tokenString.size()+1);
    secondaryToken = addStringConst(constString);
    //hasSecondaryToken = true;
    nextChar = readChar();
  }
  else if(nextChar == '\''){
    nextChar = readChar();
    tokenString = nextChar;
    token = CHARACTER;
    secondaryToken = addCharConst(nextChar);
    //hasSecondaryToken = true;
    nextChar = readChar(); //skip '
    //todo: se n tiver outro '
    nextChar = readChar();
  }
  else{ //SIMBOLOS
    //std::cout << "Read: " << nextChar;
    tokenString = nextChar;

    switch(nextChar){
    case ':':
      nextChar = readChar();
      token = COLON;
      break;

    case ';':
      nextChar = readChar();
      token = SEMI_COLON;
      // cout << token << ";" << endl;
      break;

    case ',':
      nextChar = readChar();
      token = COMMA;
      break;

    case '[':
      nextChar = readChar();
      token = LEFT_SQUARE;
      break;

    case ']':
      nextChar = readChar();
      token = RIGHT_SQUARE;
      break;

    case '{':
      nextChar = readChar();
      token = LEFT_BRACES;
      break;

    case '}':
      nextChar = readChar();
      token = RIGHT_BRACES;
      break;

    case '(':
      nextChar = readChar();
      token = LEFT_PARENTHESIS;
      break;

    case ')':
      nextChar = readChar();
      token = RIGHT_PARENTHESIS;
      break;

    case '&':
      nextChar = readChar();
      if(nextChar == '&'){
        tokenString += nextChar;
        token = AND;
        nextChar = readChar();
      }
      else token = UNKNOWN;
      break;

    case '|':
      nextChar = readChar();
      if(nextChar == '|'){
        tokenString += nextChar;
        token = OR;
        nextChar = readChar();
      }
      else token = UNKNOWN;
      break;

    case '=':
      nextChar = readChar();
      if( nextChar == '=' ){
        tokenString += nextChar;
        token = EQUAL_EQUAL;
        nextChar = readChar();
      } 
      else token = EQUALS;
      break;

    case '<':
      nextChar = readChar();
      if( nextChar == '=' ){
        tokenString += nextChar;
        token = LESS_OR_EQUAL;
        nextChar = readChar();
      } 
      else token = LESS_THAN;
      break;

    case '>':
      nextChar = readChar();
      if( nextChar == '=' ){
        tokenString += nextChar;
        token = GREATER_OR_EQUAL;
        nextChar = readChar();
      } 
      else token = GREATER_THAN;
      break;

    case '!':
      nextChar = readChar();
      if( nextChar == '=' ){
        tokenString += nextChar;
        token = NOT_EQUAL;
        nextChar = readChar();
      } 
      else token = NOT;
      break;

    case '+':
      nextChar = readChar();
      if( nextChar == '+' ){
        tokenString += nextChar;
        token = PLUS_PLUS;
        nextChar = readChar();
      } 
      else token = PLUS;
      break;

    case '-':
      nextChar = readChar();
      if( nextChar == '-' ){
        tokenString += nextChar;
        token = MINUS_MINUS;
        nextChar = readChar();
      } 
      else token = MINUS;
      break;

    case '*':
      nextChar = readChar();
      token = TIMES;
      break;

    case '/':
      nextChar = readChar();
      token = DIVIDE;
      break;

    case '.':
      nextChar = readChar();
      token = DOT;
      break;

    default:
      token = UNKNOWN;
    }
  }
  cout << "read:" << tokenString << "\ntoken:" << token << endl;
  return token;
}





