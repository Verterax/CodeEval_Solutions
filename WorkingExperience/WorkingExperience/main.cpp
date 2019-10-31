// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 139
// Working Experience

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
//#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
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


//Takes a string by reference and removes
//matching chars found in the chars[] array.
void RemChars(string& str, const char chars[], int remCharArrLen)
{
	string::iterator iter = str.begin();
	bool didErase = false;
	for (; iter != str.end(); iter++)
	{
		for (int i = 0; i < remCharArrLen; i++)
		{
			if (*iter == chars[i])
			{
				str.erase(iter);
				iter--;
				break;
			}
		}
	}
}

int getMonthNAt(const string& str, int i)
{
	if (str[i] == 'J' && str[i + 1] == 'a')
		return 0;
	else if (str[i] == 'F')
		return 1;
	else if (str[i] == 'M' && str[i + 2] == 'r')
		return 2;
	else if (str[i] == 'A' && str[i+1] == 'p')
		return 3;
	else if (str[i] == 'M' && str[i + 2] == 'y')
		return 4;
	else if (str[i] == 'J' && str[i + 2] == 'n')
		return 5;
	else if (str[i] == 'J' && str[i + 2] == 'l')
		return 6;
	else if (str[i] == 'A' && str[i + 1] == 'u')
		return 7;
	else if (str[i] == 'S')
		return 8;
	else if (str[i] == 'O')
		return 9;
	else if (str[i] == 'N')
		return 10;
	else if (str[i] == 'D')
		return 11;
	else
		cout << "ERRORRR!!!";
}

void GetMonthFromTo(const string& str, int& from, int& to)
{
	from = getMonthNAt(str, 0);
	to = getMonthNAt(str, 8);
}

void GetYearFromTo(const string& str, int& from, int& to)
{
	//3,11
	from = to = 0;
	int modifier = 1000;
	for (int i = 0; i < 4; i++)
	{
		from += (str[3 + i] - 48) * modifier;
		to += (str[11 + i] - 48) * modifier;
		modifier /= 10;
	}
	from -= 1990;
	to -= 1990;
}

int GetIndexForMonthYear(const int& month, const int& year)
{
	return (year * 12) + month;
}


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{

	bool timePeriod[360] = { false };

	char remChars[] = { ' ' };
	RemChars(line, remChars, 1);
	vector<string> periods = GetTokens(line, ';');
	int monthFrom;
	int monthTo;
	int yearFrom;
	int yearTo;

	int minIndex = 360;
	int maxIndex = -1;

	for (int i = 0; i < periods.size(); i++)
	{
		GetMonthFromTo(periods[i], monthFrom, monthTo);
		GetYearFromTo(periods[i], yearFrom, yearTo);

		int from = GetIndexForMonthYear(monthFrom, yearFrom);
		int to = GetIndexForMonthYear(monthTo, yearTo);

		if (from < minIndex) 
			minIndex = from;
		if (to > maxIndex) 
			maxIndex = to;

		for (int j = from; j <= to; j++)
		{
			timePeriod[j] = true;
		}
	}

	int monthsExp = 0;

	for (int i =minIndex; i <= maxIndex; i++)
	{
		if (timePeriod[i])
			monthsExp++;
	}


	cout << (monthsExp / 12) << endl;
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

