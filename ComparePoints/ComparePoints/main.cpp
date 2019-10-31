// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 192
// Compare Points

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#pragma region Defaults


//Parses numeric tokens out of a string
//using the specified char as the delimiter.
//Returns a vector of ints
vector<int> GetInts(const string& line, char delim)
{
	vector<int> tokens;


	return tokens;
}


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{
	//Code goes here.
	vector<int> t;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, ' '))
	{
		if (!token.empty())
			t.push_back(atoi(token.c_str()));
	}

	if (t[0] == t[2] && t[1] == t[3])
		cout << "here";
	else
	{
		if (t[3] > t[1]) cout << 'N';
		else if (t[3] < t[1]) cout << 'S';
		if (t[2] > t[0]) cout << 'E';
		else if (t[2] < t[0]) cout << 'W';
	}

	cout << endl;
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


#pragma endregion