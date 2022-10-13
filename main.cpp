#include <iostream>
#include <stdio.h>
#include <fstream>
#include "utils.h"
#include "Lexico/lexical_analyser.h"
#include "Sintatico/sintatical-analyser.h"

extern FILE* program_file;

using namespace std;

int main(int argc, const char * argv[]) {
    Utils u;
    vector<int> ruleSize;
    vector<int> ruleLeftPart;
    vector<unordered_map<int,int>> actionTable(ACTION_TABLE_SIZE);

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

    u.startParameters(ruleSize, ruleLeftPart);
    u.startActionTable(actionTable);

    parseFunction(actionTable, ruleSize, ruleLeftPart);

    token = ARRAY;
    while(token != ENDFILE){
      token = nextToken();
    }
    
    cout << "Program finished!!" << endl;
} 