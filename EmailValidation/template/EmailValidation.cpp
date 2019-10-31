// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 35
// Email Validation

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

void TemplateFunction(string line)
{
	//Code goes here.	
	int len = line.size();
	int atEncountered = 0;
	bool valid = true;
	bool openQuo = false;


	for (int i = 0; i < len; ++i)
	{
		if (line[i] == '@' && openQuo) atEncountered--; // @s in quotations don't count.

		if (line[i] == '\"'){
			openQuo = !openQuo;

			if (i != 0 && line[i + 1] != '@') valid = false;

		}
		else if (line[i] == '.')
		{
			if (i == 0 && line[1] == '.') valid = false; //Double period at start.
			else if (i == (len - 1) && line[len - 2] == '.') valid = false; //double period at end.
			else if (line[i - 1] == '.' || line[i + 1] == '.') valid = false; // two periods in a row.
		}
		else if (line[i] == '@') atEncountered++;
		else if (line[i] == '-' || line[i] == '_' || line[i] == '+') continue;
		else if (line[i] > 47 && line[i] < 58) continue; // Nums
		else if (line[i] > 64 && line[i] < 91) continue; // Capital Letters
		else if (line[i] > 96 && line[i] < 123) continue; // Capital Letters
		else valid = false;
	}

	if (atEncountered != 1) valid = false;

	//cout << ((valid) ? "true" : "false") << "(" << line<< ")" << endl;
	cout << ((valid) ? "true" : "false") << endl;

}

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { cout << "No lines\n"; return 0; }
	string allowedChars = "_-";

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		TemplateFunction(lines[i]);
	}

	return 0;
}

#pragma endregion