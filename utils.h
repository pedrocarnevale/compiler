#pragma once
#include <vector>
#include <unordered_map>

using namespace std;

#define ACTION_TABLE_SIZE 184
#define MAX_NEST_LEVEL 50
#define RULE(p) (-(p))

#define IS_SHIFT(p) ((p)>0)
#define IS_REDUCTION(p) ((p)<0)
#define IS_TYPE_KIND(k) ((k)==ARRAY_TYPE_ || \
(k)==STRUCT_TYPE_|| \
(k)==ALIAS_TYPE_ || \
(k)==SCALAR_TYPE_)

//Scope Rules
#define DF_RULE 7

#define DT_STRUCT_RULE 8
#define DT_ARRAY_RULE 9
#define DT_ALIAS_RULE 10

#define DC_DC_RULE 11
#define DC_LI_RULE 12

#define LI_COMMA_RULE 13
#define LI_IDD_RULE 14

#define DV_VAR_RULE 15

#define LP_LP_RULE 16
#define LP_IDD_RULE 17
#define LP_EPSILON_RULE 18

#define S_E_SEMICOLON 27
#define S_BLOCK_RULE 28
#define S_WHILE_RULE 29
#define S_DO_WHILE_RULE 30
#define S_IF_RULE 31
#define S_IF_ELSE_RULE 32
#define S_BREAK_RULE 33
#define S_CONTINUE_RULE 34
#define S_RETURN_RULE 35

#define E_AND_RULE 36
#define E_OR_RULE 37
#define E_L_RULE 38
#define E_LV_EQUAL_RULE 39

#define L_LESS_THAN_RULE 40
#define L_GREATER_THAN_RULE 41
#define L_LESS_EQUAL_RULE 42
#define L_GREATER_EQUAL_RULE 43
#define L_EQUAL_EQUAL_RULE 44
#define L_NOT_EQUAL_RULE 45
#define L_R_RULE 46

#define R_PLUS_RULE 47
#define R_MINUS_RULE 48
#define R_K_RULE 49

#define K_TIMES_RULE 50
#define K_DIVIDE_RULE 51
#define K_F_RULE 52

#define F_LV_RULE 53
#define F_LEFT_PLUS_PLUS_RULE 54
#define F_LEFT_MINUS_MINUS_RULE 55
#define F_RIGHT_PLUS_PLUS_RULE 56
#define F_RIGHT_MINUS_MINUS_RULE 57
#define F_PARENTHESIS_E_RULE 58
#define F_IDU_MC_RULE 59
#define F_MINUS_F_RULE 60
#define F_NOT_F_RULE 61
#define F_TRUE_RULE 62
#define F_FALSE_RULE 63
#define F_CHR_RULE 64
#define F_STR_RULE 65
#define F_NUM_RULE 66

#define LE_LE_RULE 67
#define LE_E_RULE 68
#define LE_EPSILON_RULE 69

#define LV_DOT_RULE 70
#define LV_SQUARE_RULE 71
#define LV_IDU_RULE 72

#define T_INTEGER_RULE 73
#define T_CHAR_RULE 74
#define T_BOOL_RULE 75
#define T_STRING_RULE 76
#define T_IDU_RULE 77

#define TRUE_RULE 78
#define FALSE_RULE 79
#define CHR_RULE 80
#define STR_RULE 81
#define NUM_RULE 82

#define IDD_RULE 83
#define IDU_RULE 84
#define ID_RULE 85
#define NB_RULE 86

#define MF_RULE 87
#define MC_RULE 88
#define NF_RULE 89
#define MT_RULE 90
#define ME_RULE 91
#define MW_RULE 92
#define MA_RULE 93

using namespace std;

//t_kind
typedef enum { NO_KIND_DEF_=-1, VAR_, PARAM_, FUNCTION_, FIELD_, ARRAY_TYPE_, STRUCT_TYPE_, ALIAS_TYPE_, SCALAR_TYPE_ , UNIVERSAL_} t_kind;

typedef enum{
    ACCEPT = 63,END,P,LDE,DE,DF,DT,DC,LI,DV,LP,B,LDV,LS,S,E,L,R,K,F,LE,LV,T,TRU,FALS,CHR,STR,NUM,IDD,IDU,ID,NB,MF,MC,NF,MT,ME,MW,MA
} t_nont;

//object
typedef struct object
{
    int nName;
    struct object *pNext;
    t_kind eKind;
    
    union {
        struct {
            struct object *pType;
            int nIndex;
            int nSize;
        } Var, Param, Field;
        struct {
            struct object *pRetType;
            struct object *pParams;
            int nIndex;
            int nParams;
            int nVars;
        } Function;
        struct {
            struct object *pElemType; int nNumElems;
            int nSize;
        } Array;
        struct {
            struct object *pFields;
            int nSize;
        } Struct;
        struct {
            struct object *pBaseType;
            int nSize;
        } Alias,Type;
    }_;
    
} object, *pobject;

//t_attrib
typedef struct {
    t_nont nont;
    int nSize;
    union {
        struct {
            pobject obj;
            int name;}
        ID;
        struct {
            pobject type;
        } T, E,L,R,K,F,LV;
        struct {
            pobject type;
            pobject param;
            bool err;
        } MC;
        struct {
            int label;
        } MT,ME,MW,MA;
        struct{
            pobject type;
            pobject param;
            bool err;
            int n;
        } LE;
        struct {
            pobject list;
        } LI,DC,LP;
        struct {
            pobject type;
            bool val;
        } TRU,FALS;
        struct {
            pobject type;
            int pos;
            char val;
        } CHR;
        struct {
            pobject type;
            char* val;
            int pos;
        } STR;
        struct {
            pobject type;
            int val;
            int pos;
        } NUM;  
    }_;
} t_attrib;

//error
typedef enum {
    ERR_REDCL,ERR_NO_DECL,ERR_TYPE_EXPECTED,ERR_BOOL_TYPE_EXPECTED,ERR_TYPE_MISMATCH,ERR_INVALID_TYPE,ERR_KIND_NOT_STRUCT,ERR_FIELD_NOT_DECL,ERR_KIND_NOT_ARRAY,ERR_INVALID_INDEX_TYPE,ERR_KIND_NOT_VAR,ERR_KIND_NOT_FUNCTION,ERR_TOO_MANY_ARGS,ERR_PARAM_TYPE,ERR_TOO_FEW_ARGS,ERR_RETURN_TYPE_MISMATCH
} error;

class Utils{
public:
    void startActionTable(vector<unordered_map<int,int>>& actionTable);
    void startParameters(vector<int>& ruleSize, vector<int>& ruleLeftPart);
    void Error(error code);
};

