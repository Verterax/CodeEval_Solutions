// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 102
// JSON menu IDs

#include <iostream>
#include <fstream> //fileStream
#include <string>
//#include <sstream>
//#include <vector>
//#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;

#pragma region Defaults


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string line)
{
	char num[] = "...";
	int sum = 0;
	for (unsigned int i = 0; i < line.size()-10; i++)
	{
		if (line[i] == 'L' && line[i+1] == 'a')
		{
			num[0] = line[i + 6];
			num[1] = line[i + 7];
			num[2] = line[i + 8];
			sum += atoi(num);
			num[0] = num[1] = num[2] = '.';
		}
	}

	cout << sum << endl;

}


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line != "")
			TemplateFunction(line);
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}


#pragma endregion