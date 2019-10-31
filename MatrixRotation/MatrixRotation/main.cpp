// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 178
// Matrix Rotation

#include <iostream>
#include <fstream> //fileStream
#include <string>
//#include <sstream>
//#include <vector>
#include <math.h>
//#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;

#pragma region Defaults

//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{

	int N = (int)sqrt((line.size() + 1) / 2);
	int total = N*N;

	for (unsigned int i = (N*N-N)*2; i < line.size(); i+=2)
	{
		for (int j = i; j >= 0; j-=(N*2))
		{
			cout << line[j];
			if (i != line.size() - 2) cout << ' ';
		}
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