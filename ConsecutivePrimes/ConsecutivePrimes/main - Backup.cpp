// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 187
// Consecutive Primes

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
#include <stack>
//#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;

//Reads a file, and returns the 
//contents as a vector of strings
vector<string> GetLines(const string& fileName)
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

bool ReplaceStr(string& str, const string& findOld, string& replaceNew) {
	size_t start_pos = str.find(findOld);
	if (start_pos == string::npos)
		return false;
	str.replace(start_pos, findOld.length(), replaceNew);
	return true;
}


bool IsPrimeInt(int number)
{
	if (number <= 3)
		return number > 1;
	if (number % 3 == 0 || number % 2 == 0)
		return false;
	else
		for (int i = 5; i * i <= number; i += 6)
			if (number % i == 0 || number % (i + 2) == 0)
				return false;

	return true;
}

bool IsPrime(char n)
{
	static bool primes[40];
	if (!primes[2])
	{
		for (int i = 1; i < 41; i++)
			primes[i] = IsPrimeInt(i);
	}

	return primes[n];
}


bool AllSumToPrime(const vector<int>& num, int len)
{
	if (!IsPrime(num[0] + num[len - 1]))
		return false;

	for (int i = 0; i < len-1; i++)
		if (!IsPrime(num[i] + num[i + 1]))
			return false;

	return true;
}

bool HasDupes(vector<int>& current)
{
	vector<bool> dupeCheck(current.size() + 1);

	for (int i = 0; i < current.size(); i++)
	{
		if (dupeCheck[current[i]] == true)
		{
			return true;
		}
		else
		{
			dupeCheck[current[i]] = true;
		}
	}

	return false;
}

bool IsUnique(vector<vector<int>>& uniques, vector<int>& current)
{
	int uniqueIndex = 0;
	int currentIndex = 0;
	int currentIndexOfOne = 0;
	int n = current.size();

	if (HasDupes(current))
	{
		return false;
	}

	for (int i = 0; i < n; i++)
		if (current[i] == 1)
		{
			currentIndexOfOne = i + 1;
			break;
		}

	for (int i = 0; i < uniques.size(); i++)
	{		
		//Find unique's index of 1.
		for (int j = 0; j < n; j++)
		{
			if (uniques[i][j] == 1)
			{
				uniqueIndex = j+1;
				break;
			}
		}

		bool isTheSame = true;
		currentIndex = currentIndexOfOne;
		for (int j = 0; j < n; j++)
		{		
			if (currentIndex == n) 
				currentIndex = 0;
			if (uniqueIndex == n) 
				uniqueIndex = 0;

			if (uniques[i][uniqueIndex] != current[currentIndex])
				isTheSame = false;

			uniqueIndex++;
			currentIndex++;
		}

		if (isTheSame)
			return false;
	}

	return true;
}

bool Iterate(string& num, int n)
{
	num[0]++;
	for (int i = 0; i < n; i++)
	{
		if (num[i] > 9)
		{		
			if (i == n - 1)
				return false;

			num[i] = 0;
			num[i + 1]++;
		}
	}

	return true;
}

vector<int> GetNextValid(string& last)
{
	int n = last.size();
	bool satisfactory = false;


	while (true)
	{
		if (!Iterate(last, n))
		{
			vector<int> empty;
			return empty;
		}
		else
		{
			satisfactory = true;
			vector<int> check(n + 1);

		/*	if (last[0] == 1 &&
				last[1] == 2 &&
				last[2] == 3 &&
				last[3] == 4)
				cout << "?";*/

			for (int i = 0; i < n; i++)
			{ 
				if (last[i] > n || last[i] == 0)
				{
					satisfactory = false;
					break;
				}

				if (check[last[i]] == 1)
				{
					satisfactory = false;
					break;
				}
				else
					check[last[i]] = 1;
			}

			if (!satisfactory) 
				continue;

			vector<int> valid(n);
			for (int i = 0; i < n; i++)
				valid[i] = last[i];
			return valid;
		}
	}

	 return vector<int>();
}


void PrintN(vector<int>& num)
{
	for (int i = 0; i < num.size(); i++)
		cout << num[i];
}

void PrintAllUniqueValids(int n)
{
	vector<vector<int>> uniques;
	stringstream ss;
	int count = 0;
	for (int i = 0; i < n; i++)
		ss << 0;
	string str = ss.str();
	for (int i = 0; i < n; i++) str[i] -= 48;

	while (true)
	{
		vector<int> next = GetNextValid(str);
		if (next.empty())
			break;

		//bool allSumPrime = AllSumToPrime(next, n);

		//if (allSumPrime)
		//{
			if (IsUnique(uniques, next))
			{
				uniques.push_back(next);
			}
		//}
	}

	for (int i = 0; i < uniques.size(); i++)
	{
		PrintN(uniques[i]);
		cout << endl;
	}

	cout << "Found " << uniques.size() << " unique sequences for N = " << n << endl;
}



void PrintAllValids(int n)
{
	stringstream ss;
	int count = 0;
	for (int i = 0; i < n; i++)
		ss << 0;
	string str = ss.str();
	for (int i = 0; i < n; i++) str[i] -= 48;

	while (true)
	{
		vector<int> valid = GetNextValid(str);
		if (valid.empty()) break;

		PrintN(valid);
		count++;
		cout << endl;
	}
	cout << "Total valid for n = " << n << " = " << count << endl;
}


vector<vector<pair<char, char>>> GetPrimeEntities(int n)
{
	vector<vector<pair<char, char>>> entities(n+1);

	for (char i = 1; i <= n; i++)
	{
		for (char j = 1; j <= n; j++)
		{
			if (j == i) continue;

			if (IsPrime(i + j))
			{
				entities[i].push_back(pair<char, char>(i, j));
			}
		}
	}

	return entities;
}

//vector<int> GetSequenceFromEntities(vector<vector<pair<char, char>>>& entities, vector<int> loc)
//{
//	int n = loc.size();
//	vector<int> sequence(n);
//
//	for (int a = 0; a < n; a++)
//		sequence[a] = entities[a][loc[a]].first;
//
//	return sequence;
//}


vector<int> GetSequence(vector<pair<char, char>>& current)
{
	vector<int> sequence;

	for (unsigned int i = 0; i < current.size(); i++)
	{
		sequence.push_back(current[i].first);
	}
	return sequence;
}


vector<pair<char, char>> FindMatchesWith(
	vector<vector<pair<char, char>>>& pairs, 
	pair<char, char>& matchWith,
	vector<pair<char, char>>& current)
{	
	bool dontAdd = false;
	vector<pair<char, char>> matches;
	int n = pairs.size() - 1;
	for (unsigned int i = 0; i < pairs[matchWith.second].size(); i++)
	{
		if (matchWith.second == pairs[matchWith.second][i].first)
		{
			dontAdd = false;
			pair<char,char> check = pairs[matchWith.second][i];
			for (int j = 0; j < current.size(); j++)
			{
				if (current[j].first == check.second &&
					j != n-2)
				{
					dontAdd = true;
					break;
				}				
			}

			if (!dontAdd)
				matches.push_back(check);
		}		
	}

	return matches;
}

bool HasDupes(vector<pair<char, char>>& current)
{
	bool* dupes = new bool[current.size()+1]();
	for (int i = 0; i < current.size(); i++)
	{
		if (dupes[current[i].first])
		{
			delete dupes;
			return true;
		}
		else
		{
			dupes[current[i].first] = true;
		}
	}

	delete dupes;
	return false;
}

void RemoveDupeMatches(
	vector<pair<char, char>>& matches,
	vector<pair<char, char>>& current)
{
	
	for (vector<pair<char, char>>::iterator mIter = matches.begin(); mIter != matches.end(); mIter++)
	{
		for (int i = 0; i < current.size(); i++)
		{
			if (current[i].first == (*mIter).second)
				mIter = matches.erase(mIter);

			if (mIter == matches.end()) return;
		}		
	}
}

void WalkPairs(
	vector<vector<pair<char, char>>>& pairs,
	vector<vector<int>>& found,
	vector<pair<char, char>>& current)
{
	if (current.size() == pairs.size()-1)
	{
		vector<int> sequence = GetSequence(current);
		if (IsUnique(found, sequence))
			found.push_back(sequence);
	}
	else
	{
		vector<pair<char, char>> matches = FindMatchesWith(pairs, current[current.size() - 1], current);

		if (!matches.empty())
		{
			for (unsigned int i = 0; i < matches.size(); i++)
			{				
				current.push_back(matches[i]);
				WalkPairs(pairs, found, current);
				current.pop_back();
			}
		}
	}
}

	
vector<vector<int>> GenerateUniqueSequences(int n)
{
	vector<vector<pair<char, char>>> pairs = GetPrimeEntities(n);
	vector<vector<int>> found; 
	vector<pair<char,char>> current;
	
	for (int i = 0; i < pairs[1].size(); i++)
	{
		current.push_back(pairs[1][i]);
		WalkPairs(pairs, found, current);
		current.pop_back();
	}
	
	return found;
}


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	if (file.is_open())
	{
		int lowestCommon = 0;
		while (getline(file, line))
		{
			int n = atoi(line.c_str());		
		}	


		for (int n = 2; n < 20; n++)
		{
			if (n % 2 == 0)
			{
				vector<vector<int>> uniques = GenerateUniqueSequences(n);
				cout << "N = " << n <<  " = " << uniques.size() << endl;
			}
			else
			{
				cout << "N = " << n << " = " << "0" << endl;
			}
		}

	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}
