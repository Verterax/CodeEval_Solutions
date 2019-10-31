// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 26
// File Size

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#pragma region Defaults

ifstream::pos_type fileSize(const char* path)
{
	ifstream file(path, ifstream::ate | ifstream::binary);
	return file.tellg();
}

int main(int argc, char* argv[])
{
	cout << fileSize(argv[1]);

	return 0;
}

#pragma endregion