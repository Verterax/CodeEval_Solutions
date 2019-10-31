// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 211
// Chardonnay or Cabernet

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
//#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;
using std::cout;
using std::endl;

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


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{
	//Code goes here.
	vector<string> tokens = GetTokens(line, ' ');
	vector<int> foundIndexes;
	int charCount = tokens[tokens.size() - 1].size();;

	for (unsigned int w = 0; w < tokens.size() - 2; w++) //Choose a word
	{
		bool inWord = false;
		for (int c = 0; c < charCount; c++) //See if each char is in the word
		{
			bool containsC = false; //assume its not
			for (unsigned int i = 0; i < tokens[w].size(); i++) //Scan each letter in the word
			{
				if (tokens[w][i] == tokens[tokens.size()-1][c])
				{
					tokens[w][i] -= 95;
					containsC = true;
					break;
				}
			}
			if (containsC)
			{
				if (c == charCount - 1)
					inWord = true;
				continue;
			}
			else
			{
				break;
			}
		}

		if (inWord) foundIndexes.push_back(w);
	}



	for (unsigned int i = 0; i < foundIndexes.size(); i++)
	{
		for (unsigned int j = 0; j < tokens[foundIndexes[i]].size(); j++)
		{
			if (tokens[foundIndexes[i]][j] < 50)
				tokens[foundIndexes[i]][j] += 95;
		}


		cout << tokens[foundIndexes[i]];
		if (i != foundIndexes.size() - 1) cout << ' ';
	}

	if (foundIndexes.size() == 0)
		cout << "False";


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