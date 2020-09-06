#include "instruction.h"

Instruction::Builder* Instruction::builder() {
	return new Builder;
}

Instruction* Instruction::Builder::create() {
	Instruction* ins = new Instruction;
	ins->opt = Opt;
	ins->value1 = value1;
	ins->value2 = value2;
	ins->value3 = value3;
	delete this;
	return ins;
}

Instruction::Instruction() {
	value1 = (Value*)NULL;
	value2 = (Value*)NULL;
	value3 = (Value*)NULL;
	opt = NUL;
}

Instruction::~Instruction() {
}

Instruction::Builder::Builder() {
	value1 = (Value*)NULL;
	value2 = (Value*)NULL;
	value3 = (Value*)NULL;
	Opt = NUL;
}

Instruction::Builder::~Builder() {
	
}

Instruction::Builder* Instruction::Builder::value(Value* value) {
	if (value1 == (Value*)NULL) {
		value1 = value;
	}
	else if(value2 == (Value*)NULL) {
		value2 = value;
	}
 	else if(value3 == (Value*)NULL) {
 		value3 = value;
	}
	return this;
}

Instruction::Builder* Instruction::Builder::opt(OptCode opt) {
	this->Opt = opt;
	return this;
}
