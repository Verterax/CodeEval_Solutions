// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 152
// Age Distribution

#include <iostream>
#include <fstream> //fileStream
#include <string>
using namespace std;

#pragma region Defaults

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			int age = atoi(line.c_str());

			if (age < 0 || age > 100)
				cout << "This program is for humans";
			else
			{
				if (age < 3)
					cout << "Still in Mama's arms";
				else if (age < 5)
					cout << "Preschool Maniac";
				else if (age < 12)
					cout << "Elementary school";
				else if (age < 15)
					cout << "Middle school";
				else if (age < 19)
					cout << "High school";
				else if (age < 23)
					cout << "College";
				else if (age < 66)
					cout << "Working for the man";
				else if (age < 101)
					cout << "The Golden Years";
			}
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


#pragma endregion