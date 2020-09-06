#include "main.h"

void read() {
	
}

int main() {
	List<int> list;
	list.set(200, 2);
	list.set(200, 102);
	list.set(20000000, 203);
	printf("%d\n", list.get(200));
	while (true);
	return 0;
}
