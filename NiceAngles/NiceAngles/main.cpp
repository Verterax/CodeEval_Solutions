// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 160
// Nice Angles

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <math.h>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);

	double fraction = 0;
	int whole = 0;
	int seconds = 0;
	int minutes = 0;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			fraction = stod(line);
			whole = (int)floor(fraction);
			fraction -= (double)whole;
			seconds = (int)(3600 * fraction);
			minutes = seconds / 60;
			seconds %= 60;
			printf("%01u.%02u'%02u\"\n", whole, minutes, seconds);
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}