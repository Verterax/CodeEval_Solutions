// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 20
// Lowercase

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#pragma region Defaults

vector<string> GetLines(string fileName)
{
	string line;
	vector<string> lines;
	ifstream file(fileName);

	if (file.is_open())
		while (getline(file, line))
			lines.push_back(line);
	else
		cout << "Unable to open file.\n";
	file.close();

	return lines;
}


void TemplateFunction(string line)
{
	int len = line.size();
	for (int c = 0; c < len; ++c)
		if (line[c] > 64 && line[c] < 91)
			line[c] += 32;
	cout << line << endl;

}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
		TemplateFunction(lines[i]);

	return 0;
}

#pragma endregion