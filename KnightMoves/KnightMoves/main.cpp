// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 180
// Knight Moves

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
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
		if (!token.empty())
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


bool CRange(char C)
{
	return (C >= 'a' && C <= 'h');
}

bool NRange(char N)
{
	return (N >= '1' && N <= '8');
}

//Template function set to run on each
//line read from the text file.
void TemplateFunction(string line)
{
	char C = line[0];
	char N = line[1];
	vector<string> positions;

	//Get Top
	N += 2;
	if (NRange(N))
	{
		C--;
		if (CRange(C))
			positions.push_back(string() + C + N);
		C += 2;
		if (CRange(C))
			positions.push_back(string() + C + N);
		C--;
		
	}
	N -= 2;

	//Get Bottom
	N -= 2;
	if (NRange(N))
	{
		C--;
		if (CRange(C))
			positions.push_back(string() + C + N);
		C += 2;
		if (CRange(C))
			positions.push_back(string() + C + N);
		C--;

	}
	N += 2;

	//Get Left
	C -= 2;
	if (CRange(C))
	{
		N--;
		if (NRange(N))
			positions.push_back(string() + C + N);
		N += 2;
		if (NRange(N))
			positions.push_back(string() + C + N);
		N--;

	}
	C += 2;

	//Get Right
	C += 2;
	if (CRange(C))
	{
		N--;
		if (NRange(N))
			positions.push_back(string() + C + N);
		N += 2;
		if (NRange(N))
			positions.push_back(string() + C + N);
		N--;

	}
	C -= 2;
	sort(positions.begin(), positions.end());

	for (unsigned int i = 0; i < positions.size(); i++)
	{
		cout << positions[i];
		if (i != positions.size() - 1) cout << ' ';
	}


	cout << endl;
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

//
//////Alternate Main Function for challenges which reads
//////All lines from the text file before proceeding.
//int main(int argc, char* argv[])
//{
//	if (argc == 1) { cout << "No file\n" << endl; return 0; }
//
//	//Reads text-file lines into vector of strings.
//	vector<string> lines = GetLines(argv[1]); 
//
//	int lineCount = lines.size();
//	if (lineCount == 0) { cout << "No lines\n"; return 0; }
//
//	for (int i = 0; i < lineCount; i++)
//	{
//		//Evaluate lines.
//		TemplateFunction(lines[i]);
//	}
//
//	return 0;
//}
//

#pragma endregion