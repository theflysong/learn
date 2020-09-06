#ifndef __HEAD__
#define __HEAD__

#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <windows.h>
using std::ios;
using std::vector;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::istream;
using std::ostream;
using std::iostream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::string;
using std::map;
using std::stack;
using std::queue;
using std::cerr;
using std::endl;
using std::map;

void _assert(bool condition,string fileIn,int lineIn);

#define null (0)

#ifdef __DEBUG__
	#define assert(condition) _assert(condition,__FILE__,__LINE__)
	#define assertNull(condition) assert(condition != null)
#else
	#define assert(condition)
	#define assertNull(condtion)
#endif

inline void ErrorExit() {
    Sleep(10000);
    exit(-1);
}

inline void NormalExit() {
    Sleep(1000);
    exit(0);
}

template<typename T>class List {
	T* array;
	int length;
public:
	List() {
		array = new T[20];
		length = 20;
	}
	T get(int sub) {	
		if (sub > length) {
			extra(2 * sub - length);
		}
		return array[sub];
	}
	void set(int sub,T obj) {
		if (sub > length) {
			extra(2 * sub - length);
		}
		array[sub] = obj;
	}
	void extra(int len) {
		T* old = array;
		array = new T[length + len];
		for (int i = 0 ; i < length ; i ++) {
			array[i] = old[i];
		}
		delete old;
		length += len;
	}
	~List(){
		delete array;
		array = (T*)NULL;
		length = 0;
	}
};

#endif
