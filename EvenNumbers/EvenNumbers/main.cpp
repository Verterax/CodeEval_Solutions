// By Christopher Caldwell
// chris@codehadouken.com
// Challenge N
// Challenge Name
#include <iostream>
#include <fstream> //fileStream
#include <string>
using namespace std;
int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	string line;
	ifstream file(argv[1]);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			if ((line[line.size() - 1] - 48) % 2 == 1)
				cout << '0';
			else
				cout << '1';
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