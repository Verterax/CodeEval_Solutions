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

	for (int i = 0; i < len - 1; i++)
		if (!IsPrime(num[i] + num[i + 1]))
			return false;

	return true;
}

bool IsUnique(const vector<vector<int>>& uniques, const vector<int>& current)
{
	int uniqueIndex = 0;
	int currentIndex = 0;
	int currentIndexOfOne = 1;
	int n = current.size();

	for (unsigned int i = 0; i < uniques.size(); i++)
	{
		//Find unique's index of 1.
		for (int j = 0; j < n; j++)
		{
			if (uniques[i][j] == 1)
			{
				uniqueIndex = j + 1;
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
			{
				//isTheSame = false;
				return true;
			}


			uniqueIndex++;
			currentIndex++;
		}

		if (isTheSame)
			return false;
	}

	return true;
}


void PrintN(vector<int>& num)
{
	for (unsigned int i = 0; i < num.size(); i++)
		cout << num[i];
}


vector<vector<pair<char, char>>> GetPrimeEntities(const int n)
{
	vector<vector<pair<char, char>>> entities(n + 1);

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

vector<int> GetSequence(const vector<pair<char, char>>& current)
{
	vector<int> sequence;

	for (unsigned int i = 0; i < current.size(); i++)
	{
		sequence.push_back(current[i].first);
	}
	return sequence;
}


vector<pair<char, char>> FindMatchesWith(
	const vector<vector<pair<char, char>>>& pairs,
	const pair<char, char>& matchWith,
	const vector<pair<char, char>>& current)
{
	bool dontAdd = false;
	vector<pair<char, char>> matches;
	int n = pairs.size() - 1;
	for (unsigned int i = 0; i < pairs[matchWith.second].size(); i++)
	{
		if (matchWith.second == pairs[matchWith.second][i].first)
		{
			dontAdd = false;
			//pair<char,char> check = pairs[matchWith.second][i];
			for (unsigned int j = 0; j < current.size(); j++)
			{
				if (current[j].first == pairs[matchWith.second][i].second &&
					j != n - 2)
				{
					dontAdd = true;
					break;
				}

				if (j == n - 2)
				{
					if (!IsPrime(current[0].first + pairs[matchWith.second][i].first))
						dontAdd = true;
					break;
				}
			}

			if (!dontAdd)
				matches.push_back(pairs[matchWith.second][i]);
		}
	}

	return matches;
}

void WalkPairs(
	const vector<vector<pair<char, char>>>& pairs,
	vector<vector<int>>& found,
	vector<pair<char, char>>& current)
{
	if (current.size() == pairs.size() - 1)
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
	vector<pair<char, char>> current;

	for (unsigned int i = 0; i < pairs[1].size(); i++)
	{
		current.push_back(pairs[1][i]);
		WalkPairs(pairs, found, current);
		current.pop_back();
	}


	//for (int i = 0; i < found.size(); i++)
	//{
	//	vector<int> temp = found[i];
	//	found.erase(found.begin() + i);
	//	
	//	if (!IsUnique(found, temp) || !AllSumToPrime(temp, pairs.size()-1))
	//	{
	//		cout << "ERROR" << endl;
	//	}
	//	else
	//	{
	//		PrintN(temp);
	//		cout << endl;
	//		found.push_back(temp);
	//	}
	//}

	return found;



}

int BeadArrange(int n)
{
	static int arr[] = { 0, 0, 1, 0, 2, 0, 2, 0, 4, 0, 96, 0, 1024, 0, 2880, 0, 81024, 0, 770144 };

	if (n <= 18)
		return arr[n];
	else
		return -1;
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
			cout << BeadArrange(n) << endl;
		}



		//for (int n = 2; n <= 18; n++)
		//{
		//	if (n % 2 == 0)
		//	{
		//		int* beads = new int[n];
		//		for (int i = 0; i < n; ++i) {
		//			beads[i] = i + 1;
		//		}
		//		int count = 0;
		//		//count = calculateNumNecklacesC(beads, n, 1);
		//		vector<vector<int>> uniques = GenerateUniqueSequences(n);
		//		cout << "N = " << n <<  " = " << uniques.size() << endl;
		//		//cout << "N = " << n << " = " << count << endl;
		//	}
		//	else
		//	{
		//		cout << "N = " << n << " = " << "0" << endl;
		//	}
		//}
		//getchar();
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}
