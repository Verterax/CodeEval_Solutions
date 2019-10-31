// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 45
// Reverse And Add

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
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

bool IsPalindrome(string strNum)
{
	int front = 0;
	int back = strNum.size() - 1;

	while (front < back)
	{
		if (strNum[front] != strNum[back])
			return false;

		front++;
		back--;
	}

	return true;
}

void ReverseAndAdd(string strNum)
{
	//Code goes here.
	int num = atoi(strNum.c_str());
	int additions = 0;
	stringstream ss;

	while (true)
	{
		if (IsPalindrome(strNum))
		{
			cout << additions << ' ' << strNum << endl;
			return;
		}

		//Do addition
		std::reverse(strNum.begin(), strNum.end());
		num += atoi(strNum.c_str());
		ss << num;
		strNum = ss.str();
		ss.str(string());
		ss.clear();

		++additions;
	}
	
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
		ReverseAndAdd(lines[i]);
	}

	return 0;
}

#pragma endregion