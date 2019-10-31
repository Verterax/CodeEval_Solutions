// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 96
// Swap Case

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <ctype.h> //tolower, toUpper
using namespace std;
int main(int argc, char* argv[])
{
	if (argc == 1) 
	{ cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			for (unsigned int i = 0; i < line.size(); i++)
			{
				if (isalpha(line[i]))
				{
					if (isupper(line[i]))
						cout << (char)(line[i] + 32);
					else
						cout << (char)(line[i] - 32);
				}
				else
					cout << line[i];
			}
			cout << endl;
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();
	return 0;
}