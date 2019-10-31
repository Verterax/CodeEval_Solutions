// By Christopher Caldwell
// chris@codehadouken.com

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

vector<string> GetLines(string fileName);
void function(string line);

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file" << endl; return 0; }
	string fileName = argv[1];
	vector<string> lines = GetLines(fileName);
	int lineCount = lines.size();
	if (lineCount < 1) { cout << "No lines"; return 0; }
	
	string line;
	for (int i = 0; i < lineCount; i++)
	{
		function(line);
	}

	return 0;
}

void function(string line)
{
	//Code goes here.
	//cout << line << endl;
}

vector<string> GetLines(string fileName)
{
	string line;
	vector<string> lines;

	ifstream file(fileName);

	if (file.is_open())
	{
		stringstream buff;
		buff << file.rdbuf();
		lines.push_back(buff.str());
	}
	else
	{
		cout << "Unable to open file.";
	}
	file.close();

	return lines;
}