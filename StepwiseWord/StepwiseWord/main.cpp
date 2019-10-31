// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 202
// Stepwise Word

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


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line, ' ');

	int maxLen = 0;
	int maxIndex = -1;
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].size() > maxLen)
		{
			maxLen = tokens[i].size();
			maxIndex = i;
		}
	}

	for (int i = 0; i < maxLen; i++)
	{
		for (int a = 0; a < i; a++)
			cout << '*';
		cout << tokens[maxIndex][i];
		if (i != maxLen - 1) cout << ' ';
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