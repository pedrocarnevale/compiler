#include "../utils.h"
#include <stack>

using namespace std;

pobject search (int aName);
extern void semantics(int rule);
int endBlock();
pobject define(int aName);
pobject find (int aName);
int newBlock(void);
int newLabel(void);
bool CheckTypes(pobject t1,pobject t2);