#include <iostream>

using namespace std;

int gi;

int main() {
	gi = 12;
	char buf[10];

	buf[0] = 0xc7;
	buf[1] = 0x05;
	*((int*)&buf[2]) = (int)&gi;
	*((int**)&buf[2]) = &gi;
	_asm {
		jmp buf;
	}
	
	return 0;

}