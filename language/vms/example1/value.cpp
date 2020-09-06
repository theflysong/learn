#include "value.h"

Value::Type Value::getType() {
	return this->type;
}

void Value::changeType(Type type) {
	this->type = type;
}

void* Value::getPtr() {
	return this->ptr;
}

void Value::keepValue() {
	this->keep = true;
}

char* Value::getAsBytePtr() {
	return this->pbyte; 
}

short* Value::getAsShortPtr() {
	return this->pshort;
}

int* Value::getAsIntPtr() {
	return this->pint;
}

long long* Value::getAsLongPtr() {
	return this->plong;
}

char* Value::getAsCharPtr() {
	return this->pchar;
}

string* Value::getAsStringPtr() {
	return this->pstring;
}

bool* Value::getAsBoolPtr() {
	return this->pbool;
}

Value* Value::getAsObjectPtr() {
	return this->pobject;
}

Value::~Value() {
	if (! keep){
		delete ptr;
	}
	keep = false;
}

Value::Value() {
	this->type = UNKNOW; 
}

Value::Builder::Builder() {
	this -> Type = UNKNOW; 
}

Value::Builder::~Builder() {
	
}

Value::Builder* Value::builder() {
	return new Value::Builder;
}

Value* Value::Builder::create() {
	Value* value = new Value;
	value->changeType (Type);
	delete this;
	return value;
}
Value::Builder* Value::Builder::type(Value::Type type) {
	this -> Type = type;
	return this;
}
