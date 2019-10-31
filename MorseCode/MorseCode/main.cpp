// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 116
// Morse Code

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
//#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
#include <map>
using namespace std;
using std::cout;
using std::endl;

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
		//if (!token.empty())
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

// ptr++;
//switch (*ptr)
//{
//case '-':
//	break;
//case '.':
//	break;
//case ' ':
// cout << '';
//	break;
//}


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string line, map<string, char>& morseMap)
{
	vector<string> message = GetTokens(line, ' ');

	for (int i = 0; i < message.size(); i++)
	{
		cout << morseMap[message[i]];
	}

	cout << endl;

}

map<string, char> GetMorseMap()
{
	map<string, char> morseMap;

	morseMap.emplace(".-", 'A');
	morseMap.emplace("-...", 'B');
	morseMap.emplace("-.-.", 'C');
	morseMap.emplace("-..", 'D');
	morseMap.emplace(".", 'E');
	morseMap.emplace("..-.", 'F');
	morseMap.emplace("--.", 'G');
	morseMap.emplace("....", 'H');
	morseMap.emplace("..", 'I');
	morseMap.emplace(".---", 'J');
	morseMap.emplace("-.-", 'K');
	morseMap.emplace(".-..", 'L');
	morseMap.emplace("--", 'M');
	morseMap.emplace("-.", 'N');
	morseMap.emplace("---", 'O');
	morseMap.emplace(".--.", 'P');
	morseMap.emplace("--.-", 'Q');
	morseMap.emplace(".-.", 'R');
	morseMap.emplace("...", 'S');
	morseMap.emplace("-", 'T');
	morseMap.emplace("..-", 'U');
	morseMap.emplace("...-", 'V');
	morseMap.emplace(".--", 'W');
	morseMap.emplace("-..-", 'X');
	morseMap.emplace("-.--", 'Y');
	morseMap.emplace("--..", 'Z');

	morseMap.emplace(".----", '1');
	morseMap.emplace("..---", '2');
	morseMap.emplace("...--", '3');
	morseMap.emplace("....-", '4');
	morseMap.emplace(".....", '5');
	morseMap.emplace("-....", '6');
	morseMap.emplace("--...", '7');
	morseMap.emplace("---..", '8');
	morseMap.emplace("----.", '9');
	morseMap.emplace("-----", '0');

	morseMap.emplace("", ' ');

	return morseMap;
}


int main(int argc, char* argv[])
{
	map<string, char> morseMap = GetMorseMap();

	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			TemplateFunction(line, morseMap);
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