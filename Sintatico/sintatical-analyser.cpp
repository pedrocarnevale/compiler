#include "sintatical-analyser.h"
#include "../Lexico/lexical_analyser.h"
#include "../Semantico/semantic_analyser.h"
#include "../utils.h"
#include <stack>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

stack<int> sintaticalStack;

void parseFunction(vector<unordered_map<int,int>>& actionTable, vector<int>& ruleSize, vector<int>& ruleLeftPart){
    int final_state = 1;
    int q = 0;
    sintaticalStack.push(q);
    int a = nextToken();

    do{
        if(actionTable[q].count(a) > 0){
            int p = actionTable[q][a];

            if(IS_SHIFT(p)){
                sintaticalStack.push(p);
                a = nextToken();
                cout<<"next token: "<<a<<endl;
            }

            else if(IS_REDUCTION(p)){
                int r = RULE(p);
                cout << "Rule: " << r << endl;

                for(int i = 0; i<ruleSize[r]; i++){
                    sintaticalStack.pop();
                }

                sintaticalStack.push(actionTable[sintaticalStack.top()][ruleLeftPart[r]]);
                semantics(r);
            }

            else{
                cout << "Error, in line:" << line << endl;
                exit(-1);
            }
            q = sintaticalStack.top();
        }

        else{
            cout << "Error, in line:"<< line << endl;
            exit(-1);
        }
    }while(q != final_state);
}