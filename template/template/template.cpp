// By Christopher Caldwell
// chris@codehadouken.com
// Challenge N
// Challenge Name

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
//#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;
vector<string> GetLines(const string& fileName);
vector<string> GetTokens(const string& line, char delim);
vector<int> GetInts(const string& line, char delim);
void RemChars(string& str, const char chars[], int remCharArrLen);
bool ReplaceStr(string& str, const string& findOld, string& replaceNew);
bool IsPrime(int number);

//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{
	//Code goes here.
	//vector<string> tokens = GetTokens(line);
	//sort(tokens.begin(), tokens.end());
	cout << line << endl;

}

int main(int argc, char* argv[])
{
	//if (argc == 1) { cout << "No file\n" << endl; return 0; }

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


#pragma region Methods I might use.

//Best method to test for number primality?
bool IsPrime(int number)
{
	if (number <= 3)
		return number > 1;
	if (number % 3 == 0 || number % 2 == 0)
		return false;
	else
		for (int i = 5; i * i <= number; i += 6)
			if (number % i == 0 || number % (i + 2) == 0)
				return false;

	return true;
}

int Factorial(int n)
{
    int result = 1;
    for (int i = 1; i <= n; i++)
        result *= i;
    return result;
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

bool ReplaceStr(string& str, const string& findOld, string& replaceNew) {
	size_t start_pos = str.find(findOld);
	if (start_pos == string::npos)
		return false;
	str.replace(start_pos, findOld.length(), replaceNew);
	return true;
}





//
////Console Input Main
//int main()
//{
//	cout << "Enter input, and press enter." << endl;
//	cout << "Type 'X' to exit." << endl;
//	string line;
//	int enterCount = 0;
//
//		while (getline(cin, line))
//		{
//			if (line.empty()) enterCount++;
//			if (line == "X" || line == "x" || enterCount > 1)
//				return 0;
//
//			TemplateFunction(line);
//		}
//
//	return 0;
//}

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