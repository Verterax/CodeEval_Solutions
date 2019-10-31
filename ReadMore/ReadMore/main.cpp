// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 167
//  Read More

#include <iostream>
#include <fstream> //fileStream
#include <string>
using namespace std;


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }
	const string READMORE = "... <Read More>";

	string line;
	ifstream file(argv[1]);
	bool spaceFound = false;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			spaceFound = false;
			if (line.size() <= 55)
				cout << line;
			else
			{
				line = line.substr(0, 40);
				for (int i = line.size() - 1; i > 0; i--)
				{
					if (line[i] == ' ')
					{
						spaceFound = true;
						cout << line.substr(0, i) << READMORE;
						break;
					}
				}

				if (!spaceFound)
					cout << line << READMORE;
			}

			//if (line[0] == 'A')
				//cout << "";

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
