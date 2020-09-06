#include "cfunction.h"

class Program {
	List<Value*> values;
public:
	Value* getValue(int sub) {
		return values.get(sub);
	}
	void setValue(int sub, Value* value) {
		values.set(sub, value);
	}
};
