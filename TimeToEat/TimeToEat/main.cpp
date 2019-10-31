// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 214
// Time To Eat

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;


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
		tokens.push_back(atoi(token.c_str()));
	}

	return tokens;
}


//Takes a string by reference and removes
//matching chars found in the chars[] array.
void RemChars(string& str, const char chars[], int charLen)
{
	string::iterator iter = str.begin();
	bool didErase = false;
	while (iter != str.end())
	{
		didErase = false;
		for (int i = 0; i < charLen; i++)
			if ((*iter) == chars[i])
			{
				str.erase(iter);
				didErase = true;
				break;
			}
		if (!didErase) iter++;
	}
}

struct TimeStamp
{
public:
	int hour;
	int min;
	int sec;

	TimeStamp(){};
	TimeStamp(string str)
	{
		vector<int> values = GetInts(str, ':');
		hour = values[0];
		min = values[1];
		sec = values[2];
	}
	void printString(){ printf("%02d:%02d:%02d", hour, min, sec); }
	int toSeconds() const { return hour * 3600 + min * 60 + sec; }
	bool operator < (const TimeStamp& time) const
	{
		return (toSeconds() > time.toSeconds());
	}
};

//Template function set to run on each
//line read from the text file.
void SortTimes(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line, ' ');
	vector<TimeStamp> stamps;

	for (int i = 0; i < (int)tokens.size(); i++)
	{
		const TimeStamp newStamp(tokens[i]);
		stamps.push_back(newStamp);
	}

	sort(stamps.begin(), stamps.end());

	for (int i = 0; i < (int)stamps.size(); i++)
	{
		stamps[i].printString();
		if (i != stamps.size() - 1) cout << ' ';
	}


	cout << endl;
}



int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	//Reads text-file lines into vector of strings.
	vector<string> lines = GetLines(argv[1]);

	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		SortTimes(lines[i]);
	}

	return 0;
}

