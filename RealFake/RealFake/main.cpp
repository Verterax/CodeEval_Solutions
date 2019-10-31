// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 227
// Real Fake

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

//Template function set to run on each
//line read from the text file.
void TemplateFunction(string d)
{
	const char N = 48;

	//int dubDig = 0;
	//int sigDig = 0;
	int sum = 0;
	bool dub = true;

	for (int i = 0; i < d.size(); i++)
	{
		if (isdigit(d[i]))
		{
			if (dub)
				sum += (d[i] - N) * 2;
			else
				sum += d[i] - N;
			dub = !dub;
		}
	}

	if (sum % 10 == 0)
		cout << "Real" << endl;
	else
		cout << "Fake" << endl;
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