#ifndef __CFUNCTION__
#define __CFUNCTION__

#include "instruction.h"

class Program;

typedef void(*cfunction)(Program* program);

extern map<string, cfunction> cfunctions;

void init();

#endif
