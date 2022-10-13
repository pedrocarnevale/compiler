#include <vector>
#include <unordered_map>

using namespace std;

typedef enum{
    ACCEPT = 63,END,P,LDE,DE,DF,DT,DC,LI,DV,LP,B,LDV,LS,S,E,L,R,K,F,LE,LV,T,TRU,FALS,CHR,STR,NUM,IDD,IDU,ID,NB,MF,MC,NF,MT,ME,MW,MA
} t_nont;

class Utils{
public:
    void startActionTable(vector<unordered_map<int,int>>& actionTable);
    void startParameters(vector<int>& ruleSize, vector<int>& ruleLeftPart);
};

