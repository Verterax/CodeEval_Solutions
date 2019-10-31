// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 83
// Beautiful Strings

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <vector>
#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;

#pragma region Defaults


char GetAlphaCode(char character)
{
	if (!isalpha(character))
		return -1;
	else
		return toupper(character) - 65;
}

//Template function set to run on each
//line read from the text file.
void TemplateFunction(string line)
{
	const int ALPHA_LEN = 26;
	vector<char> alphabet(ALPHA_LEN);

	for (int i = 0; i < line.size(); i++)
	{
		char index = GetAlphaCode(line[i]);

		if (index > -1)
			alphabet[index]++;
	}

	sort(alphabet.rbegin(), alphabet.rend());

	int sum = 0; 

	for (int i = 0; i < ALPHA_LEN; i++)
		sum += (ALPHA_LEN - i) * alphabet[i];

	cout << sum << endl;
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