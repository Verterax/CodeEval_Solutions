// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 230
// Football

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#pragma region Defaults

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
			if (line.length() > 0)
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
		int n = atoi(token.c_str());

		if (n != 0)
			tokens.push_back(n);
	}

	return tokens;
}


//Takes a string by reference and removes
//matching chars found in the chars[] array.
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
	//country(teams)
// Input -> 1 2 3 4 | 3 1 | 4 1
// Output-> 1:1,2,3; 2:1; 3:1,2; 4:1,3;

class Team
{
public:
	Team(){}
	Team(int teamID){ this->teamID = teamID; }
	int teamID;
	vector<int> countryIDs;
};

//Template function set to run on each
//line read from the text file.
void PrintFans(string line)
{
	//Code goes here.
	vector<string> countries = GetTokens(line, '|');
	
	map<int, Team> teamMap;
	vector<int> teamIDs;

	//Load teams for each country.
	for (int c = 0; c < countries.size(); c++)
	{
		vector<int> teams = GetInts(countries[c], ' ');

		for (int t = 0; t < teams.size(); t++)
		{
			if (teamMap.find(teams[t]) == teamMap.end())
			{
				Team newTeam(teams[t]);
				newTeam.countryIDs.push_back(c+1);
				teamMap.emplace(teams[t], newTeam);
				teamIDs.push_back(teams[t]);
			}
			else
			{
				teamMap[teams[t]].countryIDs.push_back(c+1);
			}
		}

	}

	sort(teamIDs.begin(), teamIDs.end());	
	for (int i = 0; i < teamIDs.size(); i++)
	{
		cout << teamIDs[i] << ":";
		sort(teamMap[teamIDs[i]].countryIDs.begin(), teamMap[teamIDs[i]].countryIDs.end());
		for (int c = 0; c < teamMap[teamIDs[i]].countryIDs.size(); c++)
		{
			cout << teamMap[teamIDs[i]].countryIDs[c];
			cout << ((c == teamMap[teamIDs[i]].countryIDs.size() - 1) ? ';' : ',');
		}

		if (i != teamIDs.size() - 1) cout << ' ';
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
		PrintFans(lines[i]);
	}

	return 0;
}

#pragma endregion