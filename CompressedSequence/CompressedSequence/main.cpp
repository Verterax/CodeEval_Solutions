// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 128
// Compressed Sequence

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
//#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;


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


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			//Code goes here.
			vector<int> tokens = GetInts(line, ' ');
			vector<int> output;

			int last = tokens[0];
			int count = 1;
			bool didSave = false;

			for (unsigned int i = 1; i < tokens.size(); i++)
			{
				if (tokens[i] != last)
				{
					output.push_back(count);
					output.push_back(last);
					last = tokens[i];
					count = 1;
				}
				else
					count++;
			}

			if (output.size() == 0 ||
				output[output.size() - 1] != tokens[tokens.size() - 1])
			{
				output.push_back(count);
				output.push_back(last);
			}

			for (unsigned int i = 0; i < output.size(); i++)
			{
				cout << output[i];
				if (i != output.size() - 1) cout << ' ';
			}

			cout << endl;
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}