#pragma once
#include "utils.h"

extern void semantics(int rule);

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