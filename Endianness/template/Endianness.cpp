// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 15
// Endianness

#include <iostream>
using std::cout;
using std::endl;
int main(int argc, char* argv[])
{	
	int val = 1;
	cout << ((*(char*)&val == 1) ? "LittleEndian" : "BigEndian") << endl;
}
