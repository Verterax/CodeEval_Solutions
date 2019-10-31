// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 23
// MulTables

#include <iostream>
#include <iomanip>
using namespace std;

#pragma region Defaults

int main(int argc, char* argv[])
{


	for (int i = 1; i < 13; ++i)
	{
		for (int j = 1; j < 13; ++j)
		{
			cout << i * j;
			if (j != 12)  cout << setw(4);
		}
		cout << endl;
	}

	return 0;
}

#pragma endregion