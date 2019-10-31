// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 166
// Delta Time

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
//#include <algorithm> //Sort
#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;

#pragma region Defaults


//Parses tokens out of a string
//Using a specified char as the delimiter.
vector<string> GetTokens(string line, char delim)
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
vector<int> GetInts(string line, char delim)
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
	vector<string> tokens = GetTokens(line, ' ');
	vector<int> t1 = GetInts(tokens[0], ':');
	vector<int> t2 = GetInts(tokens[1], ':');
	int time1 = t1[0] * 3600 + t1[1] * 60 + t1[2];
	int time2 = t2[0] * 3600 + t2[1] * 60 + t2[2];
	int diff = abs(time1 - time2);
	int hour = diff / 3600;
	diff -= hour * 3600;
	int min = diff / 60;
	diff -= min * 60;
	int sec = diff;

	printf("%02d:%02d:%02d\n", hour, min, sec);

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

//
//////Alternate Main Function for challenges which reads
//////All lines from the text file before proceeding.
//int main(int argc, char* argv[])
//{
//	if (argc == 1) { cout << "No file\n" << endl; return 0; }
//
//	//Reads text-file lines into vector of strings.
//	vector<string> lines = GetLines(argv[1]); 
//
//	int lineCount = lines.size();
//	if (lineCount == 0) { cout << "No lines\n"; return 0; }
//
//	for (int i = 0; i < lineCount; i++)
//	{
//		//Evaluate lines.
//		TemplateFunction(lines[i]);
//	}
//
//	return 0;
//}
//

#pragma endregion