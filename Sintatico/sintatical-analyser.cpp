#include "sintatical-analyser.h"
#include "../Lexico/lexical_analyser.h"
#include "../utils.h"
#include <stack>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;
#define IS_SHIFT(p) ((p)>0)
#define IS_REDUCTION(p) ((p)<0)
#define RULE(p) (-(p))

stack<int> pilha;

void parseFunction(vector<unordered_map<int,int>>& actionTable, vector<int>& ruleSize, vector<int>& ruleLeftPart){
    int final_state = 1;
    int q = 0;
    pilha.push(q);
    int a = nextToken();

    do{
        if(actionTable[q].count(a) > 0){
            int p = actionTable[q][a];

            if(IS_SHIFT(p)){
                pilha.push(p);
                a = nextToken();
            }

            else if(IS_REDUCTION(p)){
                int r = RULE(p);
                cout << r << endl;
                for(int i = 0; i<ruleSize[r]; i++){
                    pilha.pop();
                }

                pilha.push(actionTable[pilha.top()][ruleLeftPart[r]]);
            }

            else{
                cout << "Error, in line:" << line << endl;
                exit(-1);
            }
            q = pilha.top();
        }

        else{
            cout << "Error, in line:"<< line << endl;
            exit(-1);
        }
    }while(q != final_state);
}