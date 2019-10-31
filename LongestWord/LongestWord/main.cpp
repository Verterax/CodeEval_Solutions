// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 111
// Longest Word

#include <iostream>
#include <fstream> //fileStream
#include <string>
using namespace std;

//Template function set to run on each
//line read from the text file.
void TemplateFunction(string& line)
{
	//Code goes here.


}


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	int maxLen = 0;
	int lastSpaceIndex = -1;
	int bestIndex = -1;
	int i = 0;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			maxLen = 0;
			lastSpaceIndex = -1;
			bestIndex = -1;

			for (i = 0; i < line.size(); i++)
			{
				if (line[i] == ' ')
				{
					if (maxLen < i - (lastSpaceIndex + 1))
					{
						maxLen = i - lastSpaceIndex - 1;
						bestIndex = lastSpaceIndex + 1;
					}
					lastSpaceIndex = i;
				}
			}

			if (maxLen < line.size() - (lastSpaceIndex + 1))
			{
				maxLen = line.size() - lastSpaceIndex - 1;
				bestIndex = lastSpaceIndex + 1;
			}

			for (i = bestIndex; i < bestIndex + maxLen; i++)
				cout << line[i];

			cout << endl;
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}