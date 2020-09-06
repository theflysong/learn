#ifndef __VALUE__
#define __VALUE__
#include "head.h"

class Value {
	union {
		char* pbyte;
		short* pshort;
		int* pint;
		long long* plong;
		char* pchar;
		string* pstring;
		bool* pbool;
		Value* pobject;
		void* ptr;
	};
	bool keep;
public:
	enum Type{
		BYTE,
		SHORT,
		INT,
		LONG,
		CHAR,
		STRING,
		BOOL,
		OBJECT,
		NUL,
		UNKNOW
	}type;
	Type getType();
	void changeType(Type type);
	void* getPtr();
	void keepValue();
	char* getAsBytePtr();
	short* getAsShortPtr();
	int* getAsIntPtr();
	long long* getAsLongPtr();
	char* getAsCharPtr();
	string* getAsStringPtr();
	bool* getAsBoolPtr();
	Value* getAsObjectPtr();
	~Value();
	Value();
	class Builder {
		Value::Type Type;
	public:
		Builder();
		~Builder();
		Value* create();
		Builder* type(Value::Type type);
	};
	static Value::Builder* builder();
};

 

#endif
