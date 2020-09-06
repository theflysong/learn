#ifndef __INSTRUCTION__
#define __INSTRUCTION__

#include "value.h"

class Instruction {
public:
	enum OptCode {
		NUL,
		PUSH,
		CALL,
		RET
	};
	OptCode opt;
	Value* value1;
	Value* value2;
	Value* value3;
	Instruction();
	~Instruction();
	class Builder {
		Value* value1;
		Value* value2;
		Value* value3;
		OptCode Opt; 
	public:
		Builder();
		~Builder();
		Instruction* create();
		Builder* value(Value* value);
		Builder* opt(OptCode opt);
	};
	static Instruction::Builder* builder();
};

#endif
