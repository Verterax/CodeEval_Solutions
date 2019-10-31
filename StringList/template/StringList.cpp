// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 38
// String List

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

//return negative 1 on gone past end, otherwise, 1.
bool Increment(vector<int> &locTrack, int maxN)
{
	int size = locTrack.size();
	locTrack[size - 1]++; // increment lowest position.
	
	for (int i = size - 1; i >= 0; --i)
	{
		if (locTrack[i] == maxN)
		{
			if (i == 0)
				return true; // Attempted increment past end (Start) of array.
			else
			{
				locTrack[i] = 0;
				locTrack[i - 1]++;
			}
		}
	}

	return false;
}

void StringList(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line);
	string letters = tokens[1];
	sort(letters.begin(), letters.end());
	letters.erase(unique(letters.begin(), letters.end()), letters.end());
	int lengthN = atoi(tokens[0].c_str());
	int letterCount = letters.size();
	int i = 0;
	vector<int> locTrack(lengthN);

	for (i = 0; i < lengthN; ++i) // Initialize
	{
		locTrack[i] = 0;
	}

	bool completed = false;
	while (!completed)
	{
		for (i = 0; i < lengthN; ++i)
		{
			cout << letters[locTrack[i]];
		}
		completed = Increment(locTrack, letterCount);
		if (!completed) cout << ',';
	}
	cout << endl;

	//cout << letters << endl;
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
		StringList(lines[i]);
	}

	return 0;
}

#pragma endregion