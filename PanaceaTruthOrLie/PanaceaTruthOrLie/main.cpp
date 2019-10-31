// By Christopher Caldwell
// chris@codehadouken.com
// Challenge N
// Challenge Name

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#pragma region Defaults

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

int IntFromHex(string& str)
{
	int num = 0;
	int multiplier = 1;
	for (int i = str.size() - 1; i >= 0; i--)
	{
		str[i] -= 48;
		if (str[i] > 48) str[i] -= 39;

		num += str[i] * multiplier;
		multiplier *= 16;
	}
	return num;
}

int IntFromBin(string& str)
{
	int num = 0;
	int multiplier = 1;
	for (int i = str.size() - 1; i >= 0; i--)
	{
		if (str[i] == '1') num += multiplier;
		multiplier *= 2;
	}
	return num;
}


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line, ' ');
	bool pipeFound = false;
	int virus = 0;
	int anti = 0;

	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i][0] == '|')
		{
			pipeFound = true;
			continue;
		}

		if (!pipeFound)
			virus += IntFromHex(tokens[i]);
		else
			anti += IntFromBin(tokens[i]);
	}
	
	if (anti >= virus)
		cout << "True" << endl;
	else
		cout << "False" << endl;

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