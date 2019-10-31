// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 16
// Number of Ones

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
using namespace std;

vector<string> GetLines(string fileName)
{
	string line;
	vector<string> lines;
	ifstream file(fileName);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			lines.push_back(line);
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();

	return lines;
}
void NumberOfOnes(string line)
{
	//Code goes here.
	int num = atoi((line.c_str()));
	int bitCount = 0;
	size_t size = sizeof(int) -1;
	unsigned int max = (unsigned int)pow(2, size * 8);
	for (unsigned int i = 1; i < max;i*=2)
			if (num & i) bitCount++;
	cout << bitCount << endl;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		NumberOfOnes(lines[i]);
	}

	return 0;
}