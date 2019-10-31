// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 203
// Strings And Arrows

#include <iostream>
#include <fstream> //fileStream
#include <string>
//#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;

#pragma region Defaults

//Template function set to run on each
//line read from the text file.
void TemplateFunction(string line)
{
	const string LEFT_ARROW = "<--<<";
	const string RIGHT_ARROW = ">>-->";
	const int ARROW_LENGTH = 5;

	int count = 0;

	for (int i = 0; i < line.size() - 4; i++)
	{
		if (line[i] == '<') // Scan Left Arrow
		{
			bool foundArrow = true;
			for (int s = 0; s < ARROW_LENGTH; s++)
			{
				if (line[i + s] != LEFT_ARROW[s])
					foundArrow = false;
			}

			if (foundArrow)
			{
				count++;
				i += 3;
			}
		}
		else if (line[i] == '>') // Scan Right Arrow
		{
			bool foundArrow = true;
			for (int s = 0; s < ARROW_LENGTH; s++)
			{
				if (line[i + s] != RIGHT_ARROW[s])
					foundArrow = false;
			}

			if (foundArrow)
			{
				count++;
				i += 3;
			}
		}
	}
	cout << count << endl;
}

//Alternate Main Function for challenges which simply operate
//On single lines.
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