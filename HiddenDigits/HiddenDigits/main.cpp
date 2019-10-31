// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 122
// Hidden Digits

#include <iostream>
#include <fstream> //fileStream
using namespace std;

#pragma region Defaults

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);
	char c;
	bool found = false;

	if (file.is_open())
	{
		while (file.get(c))
		{
			if (isdigit(c))
			{
				cout << c;
				found = true;
			}
			else if (c >= 'a' && c <= 'j')
			{
				c -= 49;
				cout << c;
				found = true;
			}
			if (c == '\n')
			{
				if (!found)
					cout << "NONE";
				cout << endl;
				found = false;
			}
		}

		if (isdigit(c))
		{
			cout << c;
			found = true;
		}
		else if (c >= 'a' && c <= 'j')
		{
			c -= 49;
			cout << c;
			found = true;
		}

		if (!found)
			cout << "NONE";
		cout << endl;
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}


#pragma endregion