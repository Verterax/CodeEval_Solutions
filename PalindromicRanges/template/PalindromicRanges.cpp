// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 47
// Palindromic Ranges

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

vector<int> GetInts(string line, char delim)
{
	vector<int> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
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

bool IsPalindrome(int num)
{
	stringstream ss;
	ss << num;
	string temp = ss.str();
	std::reverse(temp.begin(), temp.end());
	return ss.str() == temp;
}

void PalindromicRanges(string line)
{
	//Code goes here.
	vector<int> tokens = GetInts(line, ' ');
	int L = tokens[0];
	int R = tokens[1];
	int palinCount, interesting, index, i, j, k;
	palinCount = interesting = index = 0;
	//int fullRange = R - L + 1;
	//bool* palinArr = new bool[fullRange];

	//Precalc palindromics.
	//for (i = L; i <= R; ++i)
	//{
	//	palinArr[index] = IsPalindrome(i);
	//	++index;
	//}

	for (i = L; i <= R; ++i) //Start of subrange
	{
		for (j = i; j <= R; ++j) //end of subrange
		{
			palinCount = 0;
			for (k = i; k <= j; ++k)
				if (IsPalindrome(k))
					palinCount++;

			if (palinCount % 2 == 0)
				interesting++;
		}
	}

	//Cleanup palindrome arr.
	//delete palinArr;

	cout << interesting << endl;

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
		PalindromicRanges(lines[i]);
	}

	return 0;
}

