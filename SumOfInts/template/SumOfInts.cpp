// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 17
// Sum Of Integers

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <climits>
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
	while (std::getline(stream, token, ','))
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

int* GetIntArray(const vector<string>& tokens)
{
	
	int len = tokens.size();
	int* intArr = new int[len];

	for (int i = 0; i < len; ++i)
		intArr[i] = atoi(tokens[i].c_str());

	return intArr;
}

int SumOfInts(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line);
	int* intArr = GetIntArray(tokens);
	int len = tokens.size();
	int currentSum, pos, high = INT_MIN;
	int subArrLen = 1;

	for (subArrLen = 1; subArrLen <= len; subArrLen++)
		for (int i = 0; i < len - subArrLen + 1; ++i) // Start scanning at 0.
		{
			currentSum = 0;
			for (pos = i; pos < i + subArrLen; pos++) //Start scanning at begin of i.
				currentSum += intArr[pos];

			if (currentSum > high) 
				high = currentSum;
		}

	return high;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	string fileName = argv[1];

	string line;
	vector<string> lines = GetLines(fileName);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		cout << SumOfInts(lines[i]) << endl;
	}

	return 0;
}

#pragma endregion