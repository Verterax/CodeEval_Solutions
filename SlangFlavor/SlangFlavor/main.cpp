// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 174
// Slang Flava

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
using namespace std;

string GetSlang()
{
	static int slangID = 0;
	int id = slangID;
	static string slangs[] = {
		", yeah!",
		", this is crazy, I tell ya.",
		", can U believe this?",
		", eh?",
		", aw yea.",
		", yo.",
		"? No way!",
		". Awesome!"
	};

	slangID++;
	if (slangID > 7) slangID = 0;

	return slangs[id];
}


//Template function set to run on each
//line read from the text file.
void TemplateFunction(string line)
{
	static bool second = false;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == '.' || line[i] == '!' || line[i] == '?')
		{
			if (second)
				cout << GetSlang();
			else
				cout << line[i];
			second = !second;
		}			
		else
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
