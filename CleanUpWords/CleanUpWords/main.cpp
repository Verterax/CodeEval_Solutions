// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 205
// Clean Up the Words

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> //Sort
#include <iomanip> //printf
#include <ctype.h> //tolower, toUpper
using namespace std;

#pragma region Defaults

//Reads a file, and returns the 
//contents as a vector of strings
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

//Parses tokens out of a string
//Using a specified char as the delimiter.
vector<string> GetTokens(string line, char delim)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		tokens.push_back(token);
	}

	return tokens;
}

//Parses numeric tokens out of a string
//using the specified char as the delimiter.
//Returns a vector of ints
vector<int> GetInts(string line, char delim)
{
	vector<int> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		tokens.push_back(atoi(token.c_str()));
	}

	return tokens;
}


//Takes a string by reference and removes
//matching chars found in the chars[] array.
void RemChars(string& str, const char chars[], int charLen)
{
	string::iterator iter = str.begin();
	bool didErase = false;
	while (iter != str.end())
	{
		didErase = false;
		for (int i = 0; i < charLen; i++)
			if ((*iter) == chars[i])
			{
				str.erase(iter);
				didErase = true;
				break;
			}
		if (!didErase) iter++;
	}
}

//Custom class template
//Exemplfies custom sort method overload.
class TempClass
{
public:
	////data
	//int value;

	bool operator < (const TempClass& c) const
	{
		//return this->value < c.value;
	}

};




//Template function set to run on each
//line read from the text file.
void TemplateFunction(string line)
{
	bool firstWord = true;
	bool writingWord = false;

	for (int i = 0; i < line.size(); i++)
	{
		if (isalpha(line[i]))
		{
			//Is it the first word?
			if (firstWord)
			{
				firstWord = false;
				writingWord = true;
			}
			else
			{
				if (!writingWord)
				{
					cout << ' ';
					writingWord = true;
				}
			}
			cout << (char)tolower(line[i]);			
		}
		else
		{
			writingWord = false;
		}
	}

	cout << endl;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	//Reads text-file lines into vector of strings.
	vector<string> lines = GetLines(argv[1]);

	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		TemplateFunction(lines[i]);
	}

	return 0;
}

#pragma endregion