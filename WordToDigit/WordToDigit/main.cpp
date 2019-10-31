// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 104
// Word To Digit

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
//#include <algorithm> //Sort
//#include <iomanip> //printf
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
		tokens.push_back(token);
	}

	return tokens;
}


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line, ';');

	for (vector<string>::iterator token = tokens.begin(); token != tokens.end(); token++)
	{
		if ((*token)[0] == 'z')
			cout << 0;
		else if ((*token)[1] == 'n')
			cout << 1;
		else if ((*token)[1] == 'w')
			cout << 2;
		else if ((*token)[1] == 'h')
			cout << 3;
		else if ((*token)[1] == 'o')
			cout << 4;
		else if ((*token)[2] == 'x')
			cout << 6;
		else if ((*token)[2] == 'v' && (*token)[0] == 's')
			cout << 7;
		else if ((*token)[2] == 'g')
			cout << 8;
		else if ((*token)[2] == 'n')
			cout << 9;
		else
			cout << 5;
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