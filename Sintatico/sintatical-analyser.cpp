#include "sintatical-analyser.h"
#include "../Lexico/lexical_analyser.h"
#include <stack>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define ACTION_TABLE_SIZE 184
#define IS_SHIFT(p) ((p)>0)
#define IS_REDUCTION(p) ((p)<0)
#define RULE(p) (-(p))

vector<string> nonTerminalVariables = {"ACCEPT","END","P","LDE","DE","DF","DT","DC","LI","DV","LP","B","LDV","LS","S","E","L","R","K","F","LE","LV","T","TRU","FALS","CHR","STR","NUM","IDD","IDU","ID","NB","MF","MC","NF","MT","ME","MW","MA"};
unordered_map<string, int> nonTerminalVariablesMap;

stack<int> pilha;
vector<unordered_map<int,int>> Action(ACTION_TABLE_SIZE);
vector<int> rulesize;
vector<int> ruleLeftPart;

void parseFunction(){
    int final_state = 1;
    int q = 0;
    pilha.push(q);
    int a = nextToken();

    startParameters();

    do{
        if(Action[q].count(a) > 0){
            int p = Action[q][a];

            if(IS_SHIFT(p)){
                pilha.push(p);
                a = nextToken();
            }

            else if(IS_REDUCTION(p)){
                int r = RULE(p);

                for(int i = 0; i<rulesize[r]; i++){
                    pilha.pop();
                }

                pilha.push(Action[pilha.top()][ruleLeftPart[r]]);
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

void startParameters(){
    int num = 63;
    for (string str: nonTerminalVariables){
        nonTerminalVariablesMap[str] = num;
        num++;
    }

    fstream fAction, fRuleSize, fRuleLeftPart;
  
    fAction.open("action.csv", ios::in);
    fRuleSize.open("ruleSize.csv", ios::in);
    fRuleLeftPart.open("ruleLeftPart.csv", ios::in);
    
    vector<int> row;
    string line, word, temp;
    int rowNum = 0, colNum = 0;

    getline(fAction, line);
  
    while (fAction >> temp) {
        rowNum = 0;
        
        getline(fAction, line);
        stringstream s(line);

        while (getline(s, word, ',')) {
            if (word == " " || word == "") Action[rowNum][colNum] = 0;
            else Action[rowNum][colNum] = stoi(word);
            rowNum++;
        }

        colNum++;
    }

    while (fRuleSize >> temp) {
        getline(fRuleSize, line);
        stringstream s(line);

        while (getline(s, word, ',')) {
            if (!word.empty()) rulesize.push_back(stoi(word));
        }
    }

    while (fRuleLeftPart >> temp) {
        getline(fRuleLeftPart, line);
        stringstream s(line);

        while (getline(s, word, ',')) {
            if (!word.empty()) ruleLeftPart.push_back(nonTerminalVariablesMap[word]);
        }
    }
}