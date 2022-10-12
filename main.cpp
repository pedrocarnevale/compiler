#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Lexico/lexical_analyser.h"
#include "Sintatico/sintatical-analyser.h"

extern FILE* program_file;

using namespace std;

int main(int argc, const char * argv[]) {
    if(argc > 1){
        program_file = fopen(argv[1],"r");
    }
    else{
        program_file = fopen("programa_novo","r");
    }
    
    if(program_file == NULL){
        cout << "The file does not exist or could not be opened" << endl;
        exit(1);
    }

    parseFunction();

    token = ARRAY;
    while(token != ENDFILE){
      token = nextToken();
    }
    
    cout << "Program finished!!" << endl;
} 