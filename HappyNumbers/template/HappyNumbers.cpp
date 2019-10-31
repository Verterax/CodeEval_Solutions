// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 39
// Happy Numbers

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
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

vector<string> GetTokens(string line)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, ' '))
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

void HappyNumber(string numStr)
{
	//Code goes here.
	int num = atoi(numStr.c_str());
	int len = numStr.size();
	int digit = 0;
	unordered_map<int, bool> beenHere;

	while (num != 1)
	{
		num = 0;
		for (int i = 0; i < len; ++i)
		{
			digit = numStr[i] - '0';
			num += digit * digit;
		}

		stringstream ss;
		ss << num;
		numStr = ss.str();
		len = numStr.size();

		if (beenHere.end() == beenHere.find(num))
		{
			beenHere.emplace(num, false);
		}
		else
		{
			break;
		}

	}

	cout << ((num == 1) ? 1 : 0) << endl;
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
		HappyNumber(lines[i]);
	}

	return 0;
}

#pragma endregion