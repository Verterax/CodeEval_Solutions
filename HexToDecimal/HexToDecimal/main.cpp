// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 67
// Hex To Decimal

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
//#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;

#pragma region Defaults

//Reads a file, and returns the 
//contents as a vector of strings
vector<string> GetLines(const string& fileName)
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
vector<string> GetTokens(const string& line, char delim)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		if (!token.empty())
			tokens.push_back(token);
	}

	return tokens;
}

//Parses numeric tokens out of a string
//using the specified char as the delimiter.
//Returns a vector of ints
vector<int> GetInts(const string& line, char delim)
{
	vector<int> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		if (!token.empty())
			tokens.push_back(atoi(token.c_str()));
	}

	return tokens;
}


//Takes a string by reference and removes
//matching chars found in the chars[] array.
void RemChars(string& str, const char chars[], int remCharArrLen)
{
	string::iterator iter = str.begin();
	bool didErase = false;
	for (; iter != str.end(); iter++)
	{
		for (int i = 0; i < remCharArrLen; i++)
		{
			if (*iter == chars[i])
			{
				str.erase(iter);
				iter--;
				break;
			}
		}
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
void TemplateFunction(string& line)
{

}


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	int num = 0;
	int multiplier = 1;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			num = 0;
			multiplier = 1;
			for (int i = line.size() - 1; i >= 0; i--)
			{
				line[i] -= 48;
				if (line[i] > 48) line[i] -= 39;

				num += line[i] * multiplier;
				multiplier *= 16;
			}

			cout << num << endl;
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