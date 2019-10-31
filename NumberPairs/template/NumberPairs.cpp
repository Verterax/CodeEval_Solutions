// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 34
// Number Pairs

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
		std::cout << "Unable to open file.\n";
	}
	file.close();

	return lines;
}

vector<string> GetTokens(string line)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, ';'))
	{
		tokens.push_back(token);
	}

	return tokens;
}

vector<int> GetInts(string line)
{
	vector<int> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, ','))
	{
		tokens.push_back(atoi(token.c_str()));
	}

	return tokens;
}

void RemChars(string& str, const char chars[], int charLen)
{
	int i;
	int strLen = str.size();
	string::iterator iter = str.begin();
	bool didErase = false;
	while (iter != str.end())
	{
		didErase = false;
		for (i = 0; i < charLen; i++)
			if ((*iter) == chars[i])
			{
				str.erase(iter);
				didErase = true;
				break;
			}
		if (!didErase) iter++;
	}
}

void NumberPairs(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line);

	if (tokens.size() == 0)
		return;

	vector<int> nums = GetInts(tokens[0]);
	stringstream ss;
	int x = atoi(tokens[1].c_str());
	int bigEnd = nums.size() - 1;
	int littleEnd = 0;
	int result;
	
	tokens.clear(); // Reuse for sorted List.

	while (bigEnd > littleEnd)
	{
		result = nums[littleEnd] + nums[bigEnd];

		if (result > x)
			bigEnd--;
		else if (result < x)
			littleEnd++;
		else
		{ 
			ss << nums[littleEnd] << ',' << nums[bigEnd];
			tokens.push_back(ss.str());
			ss.str("");
			ss.clear();
			bigEnd--;
			littleEnd++;
		}			
	}

	result = tokens.size();

	if (result == 0)
		std::cout << "NULL";
	else
	{
		for (int i = 0; i < result; ++i)
		{
			std::cout << tokens[i];
			if (i != result - 1) std::cout << ";";
		}
		
	}

	std::cout << endl;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { std::cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { std::cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		NumberPairs(lines[i]);
	}

	return 0;
}

#pragma endregion