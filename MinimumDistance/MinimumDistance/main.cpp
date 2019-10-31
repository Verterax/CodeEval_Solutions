// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 189
// Minimum Distance

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
using namespace std;

#pragma region Defaults
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


int AverageBestDistance(string& line)
{
	vector<int> houseNums = GetInts(line, ' ');
	int count = houseNums[0];
	int sum = 0;
	int minDiff = 0;
	int tempMinDiff = 0;

	for (int i = 1; i <= count; i++)
		sum += houseNums[i];

	//int flo = (int)floor((double)sum / (double)count);
	//int ce = (int)ceil((double)sum / (double)count);
	int avg = sum / count;

	for (int i = 1; i <= count; i++)
	{
		minDiff += abs(avg - houseNums[i]);
		//minDiff += abs(flo - houseNums[i]);
		//tempMinDiff += abs(ce - houseNums[i]);
	}

	//cout << (minDiff < tempMinDiff ? minDiff : tempMinDiff) << endl;
	//cout << minDiff << endl;

	return minDiff;
}

int ActualBestDistance(string &line)
{
	vector<int> houseNums = GetInts(line, ' ');
	int count = houseNums[0];
	int sum = 0;
	int bestDiff = 0;
	int currentDiff = 0;
	int maxHouse = houseNums[1];
	int minHouse = houseNums[1];

	for (int i = 1; i <= count; i++)
	{
		sum += houseNums[i];
		if (maxHouse < houseNums[i]) maxHouse = houseNums[i];
		if (minHouse > houseNums[i]) minHouse = houseNums[i];
	}

	bestDiff = sum;
	for (int i = minHouse; i <= maxHouse; i++)
	{
		currentDiff = 0;
		for (int h = 1; h <= count; h++)
		{
			currentDiff += abs(i - houseNums[h]);
		}
		if (currentDiff < bestDiff) bestDiff = currentDiff;
	}

	return bestDiff;
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
			//int avgBest = AverageBestDistance(line);
			int actual = ActualBestDistance(line);
			cout << actual << endl;
			//cout << "Avg Best: " << avgBest << " :: Actual: " << actual << endl;
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}

#pragma endregion