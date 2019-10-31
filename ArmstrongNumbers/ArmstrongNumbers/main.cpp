// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 82
// Armstrong Numbers

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
//#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;
using std::cout;
using std::endl;

#pragma region Defaults

//Template function set to run on each
//line read from the text file.
void TemplateFunction(string line)
{
	//Code goes here.
	int sum = 0;
	int N = line.size();
	int num = atoi(line.c_str());

	for (int i = N - 1; i >= 0; i--)
	{
		sum += (int)pow((double)(line[i] - 48), (double)N);
	}

	if (num == sum)
		cout << "True";
	else
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