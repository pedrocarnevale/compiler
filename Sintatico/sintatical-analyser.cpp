#include "sintatical-analyser.h"
#include "../Lexico/lexical_analyser.h"
#include <stack>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

#define ACTION_TABLE_SIZE 184
#define IS_SHIFT(p) ((p)>0)
#define IS_REDUCTION(p) ((p)<0)
#define RULE(p) (-(p))

stack<int> pilha;


void parseFunction(){
    int final_state = 1;
    int q = 0;
    pilha.push(q);
    int a = nextToken();
    do{
        if(Action[q].count(a) > 0){
            int p = Action[q][a];

            if(IS_SHIFT(p)){
                pilha.push(p);
                a = nextToken();
            }

            else if(IS_REDUCTION(p)){
                int r = RULE(p);

                for(int i = 0; i<ruleLen[r]; i++){
                    pilha.pop();
                }

                pilha.push(Action[pilha.top()][ruleLeft[r]]);
            }
            else{
                cout << "Error" << line << endl;
                exit(-1);
            }
            q = pilha.top();
        }

        else{
            cout << "Error:" << line << endl;
            exit(-1);
        }
    }while(q != final_state);
}