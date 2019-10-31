// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 136
// Racing Chars

#include <iostream>
#include <fstream> //fileStream
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	int lastDiff = 0;
	int lastIndex = -1;
	int CPIndex = -1;
	int gateIndex = -1;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			CPIndex = -1;
			gateIndex = -1;

			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] == 'C') CPIndex = i;
				if (line[i] == '_') gateIndex = i;
				if (CPIndex != -1 && gateIndex != -1)
					break;
			}

			if (CPIndex != -1)
			{
				if (lastIndex == -1) lastIndex = CPIndex;
				lastDiff = lastIndex - CPIndex;

				if (lastDiff > 0) 
					line[CPIndex] = '/';
				else if (lastDiff < 0) 
					line[CPIndex] = '\\';
				else 
					line[CPIndex] = '|';

				lastIndex = CPIndex;
			}
			else if (gateIndex != -1)
			{
				if (lastIndex == -1) lastIndex = gateIndex;
				lastDiff = lastIndex - gateIndex;

				if (lastDiff > 0) 
					line[gateIndex] = '/';
				else if (lastDiff < 0) 
					line[gateIndex] = '\\';
				else 
					line[gateIndex] = '|';

				lastIndex = gateIndex;
			}

			cout << line << endl;
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}