// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 107
// Shortest Repetition

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
//using namespace std;
using std::cout;
using std::endl;

#pragma region Defaults

//Template function set to run on each
//line read from the text file.
void TemplateFunction(std::string& line)
{
	std::string::iterator head = line.begin();
	std::string::iterator tail = line.begin() + 1;
	unsigned int len = 1;

		for (size_t i = 1; i < line.size(); i++)
		{
			if (*head != *tail)
			{
				tail++;
				len++;
				continue;
			}
			else
			{
				head++;
				tail++;
			}
		}

		cout << len << endl;
}


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	std::string line;
	std::ifstream file(argv[1]);

	if (file.is_open())
	{
		while (std::getline(file, line))
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

#pragma endregion