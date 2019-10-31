// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 103
// Lowest Unique Number

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
using namespace std;

#pragma region Defaults

//Template function set to run on each
//line read from the text file.
void TemplateFunction(string line)
{
	char numberList[9] = {0,0,0,0,0,0,0,0,0};

	for (int i = 0; i < line.size(); i += 2)
	{
		numberList[(line[i] - 49)]++;
	}

	int index = -1;
	int min = 10;

	for (int i = 0; i < 9; i++)
	{
		if (numberList[i] == 1)
		{
			min = i + 1;
			break;
		}
	}

	for (int i = 0; i < line.size(); i += 2)
	{
		if (line[i] - 48 == min)
		{
			index = i;
			break;
		}
	}


	if (index != -1)
		cout << (index/2)+1 << endl;
	else
		cout << '0' << endl;
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