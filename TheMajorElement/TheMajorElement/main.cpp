// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 132
// The Major Element

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> //Sort
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

//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{
	//Code goes here.
	vector<int> t = GetInts(line, ',');
	sort(t.begin(), t.end());

	int majorElem = -1;
	int currentCount = 1;
	int bestCount = 0;

	for (int i = 0; i < t.size() - 1; i++)
	{
		if (t[i] == t[i + 1])
		{
			currentCount++;
		}
		else
		{
			if (currentCount > bestCount)
			{
				majorElem = t[i];
				bestCount = currentCount;
			}
			currentCount = 1;
		}
	}

	if ((double)bestCount > (double)t.size() / 2.0)
		cout << majorElem << endl;
	else
		cout << "None" << endl;
}


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);
	char c;
	int n = 0;
	int board[101] = { 0 };
	char temp[4] = { 0 };
	temp[3] = 0;
	int l = 0;
	int d = 0;
	int majorElem = 0;
	int count = 0;

	if (file.is_open())
	{
		while (file.get(c))
		{
			if (c == ',')
			{
				n = atoi(temp);
				board[n]++;
				temp[0] = temp[1] = temp[2] = 0;
				d = 0;
				l++;
			}
			else if (c == '\n')
			{
				n = atoi(temp);
				board[n]++;
				temp[0] = temp[1] = temp[2] = 0;
				d = 0;

				for (int i = 0; i < 101; i++)
				{
					if (board[i] > count)
					{
						count = board[i];
						majorElem = i;
					}
					board[i] = 0;
				}

				if ((double)count > (double)l / 2.0)
					cout << majorElem << endl;
				else
					cout << "None" << endl;

				count = 0;
				l = 0;
			}
			else
			{
				temp[d] = c;
				d++;
			}
			
		}
		n = atoi(temp);
		board[n]++;
		temp[0] = temp[1] = temp[2] = 0;
		d = 0;

		for (int i = 0; i < 101; i++)
		{
			if (board[i] > count)
			{
				count = board[i];
				majorElem = i;
			}
			board[i] = 0;
		}

		if ((double)count > (double)l / 2.0)
			cout << majorElem << endl;
		else
			cout << "None" << endl;
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}

#pragma endregion