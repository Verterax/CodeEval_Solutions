// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 37
// Pangrams

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#pragma region Defaults

vector<string> GetLines(string fileName)
{
	string line;
	vector<string> lines;
	ifstream file(fileName);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			lines.push_back(line);
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();

	return lines;
}

void Pangram(string line)
{
	//Code goes here.
	char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
	int len = line.size();
	int i = 0;
	char tempChar = ' ';

	for (i = 0; i < len; ++i)
	{
		tempChar = line[i];

		if (tempChar > 64 && tempChar < 91)
		{
			tempChar += 32;
		}

		if (tempChar > 96 && tempChar < 123)
		{
			alphabet[tempChar - 97] = ' ';
		}
	}

	i = 0;
	tempChar = 0;
	for (i = 0; i < 26; ++i)
	{
		if (alphabet[i] != ' ')
		{
			cout << alphabet[i];
			tempChar = 1;
		}
	}

	if (tempChar == 0)
		cout << "NULL";

	cout << endl;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		Pangram(lines[i]);
	}

	return 0;
}

#pragma endregion