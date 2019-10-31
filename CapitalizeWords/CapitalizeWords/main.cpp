// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 93
// Capitalize Words

#include <iostream>
#include <fstream> //fileStream
#include <string>
using namespace std;


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{
	if (line[0] > 96 && line[0] < 123)
		line[0] = line[0] - 32;
	cout << line[0];
	for (int i = 1; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			if (line[i + 1] > 96 && line[i + 1] < 123)
				line[i + 1] = line[i + 1] - 32;
		}
		cout << line[i];
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