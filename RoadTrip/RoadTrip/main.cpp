// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 124
// Road Trip

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> //Sort
#include <math.h>
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;

#pragma region Defaults


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{
	//Code goes here.
	vector<int> cities;
	bool writingNum = false;
	int temp = 0;
	double digit = 0.0;
	for (unsigned int i = line.size() - 1; i > 0; i--)
	{
		if (isdigit(line[i]))
		{
			temp += (int)(pow(10.0, digit) * (line[i]-48));
			writingNum = true;
			digit++;
		}
		else
		{
			if (writingNum)
			{
				writingNum = false;
				cities.push_back(temp);
				digit = 0.0;
				temp = 0;
			}
		}
	}

	sort(cities.begin(), cities.end());

	for (unsigned int i = 0; i < cities.size(); i++)
	{
		if (i == 0)
			cout << cities[0];
		else
			cout << cities[i] - cities[i - 1];


		if (i != cities.size() - 1) cout << ',';
	}
	cout << endl;
}


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	char chars[] = { ';' };

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

#pragma endregion