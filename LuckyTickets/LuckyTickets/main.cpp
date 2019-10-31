// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 206
// Lucky Tickets

#include <iostream>
#include <fstream> //fileStream
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
//#include <algorithm> //Sort
//#include <iomanip> //printf
//#include <ctype.h> //tolower, toUpper
using namespace std;
using std::cout;
using std::endl;

//Reads a file, and returns the 
//contents as a vector of strings
vector<string> GetLines(const string& fileName)
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

//Parses tokens out of a string
//Using a specified char as the delimiter.
vector<string> GetTokens(const string& line, char delim)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		if (!token.empty())
			tokens.push_back(token);
	}

	return tokens;
}

//Parses numeric tokens out of a string
//using the specified char as the delimiter.
//Returns a vector of ints
vector<int> GetInts(const string& line, char delim)
{
	vector<int> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		if (!token.empty())
			tokens.push_back(atoi(token.c_str()));
	}

	return tokens;
}


//Takes a string by reference and removes
//matching chars found in the chars[] array.
void RemChars(string& str, const char chars[], int remCharArrLen)
{
	string::iterator iter = str.begin();
	bool didErase = false;
	for (; iter != str.end(); iter++)
	{
		for (int i = 0; i < remCharArrLen; i++)
		{
			if (*iter == chars[i])
			{
				str.erase(iter);
				iter--;
				break;
			}
		}
	}
}

bool ReplaceStr(string& str, const string& findOld, string& replaceNew) {
	size_t start_pos = str.find(findOld);
	if (start_pos == string::npos)
		return false;
	str.replace(start_pos, findOld.length(), replaceNew);
	return true;
}


void Iterate(string& digits)
{
	digits[digits.size() - 1]++;
	for (int i = digits.size() - 1; i > 0; i--)
	{
		if (digits[i] == 10)
		{
			digits[i] = 0;
			digits[i - 1]++;
		}
	}
}

void Iterate(char* digits, int L)
{
	digits[L - 1]++;
	for (int i = L - 1; i > 0; i--)
	{
		if (digits[i] == 10)
		{
			digits[i] = 0;
			digits[i - 1]++;
		}
	}
}

bool IsLucky(string& digits, size_t mid)
{
	int sum = 0;
	for (size_t i = 0; i < digits.size(); i++)
	{
		if (i >= mid)
			sum -= digits[i];
		else
			sum += digits[i];
	}
	return sum == 0;
}

void PrintNumber(string& digits)
{
	for (size_t i = 0; i < digits.size(); i++)
	{
		if (digits[i] >= 10)
		cout << (char)(digits[i] + 48);
	}
	//cout << endl;
}

int SumDigits(char* digits, int L)
{
	int sum = 0;
	for (int i = 0; i < L; i++)
		sum += digits[i];
	return sum;
}

void PrintSumsOfN(int* possibilities, int maxPos)
{
	int total = 0;
	int sumOfSquares = 0;
	int s = 0;
	for (int i = 0; i < maxPos; i++)
	{
		s = possibilities[i];
		printf("%d:\t%d\n", i, s);
		total += s;
		sumOfSquares += (int)pow(s, 2);
	}
	cout << "Total =\t" << total << endl;
	cout << "Sum of Squares:\t" << sumOfSquares << endl;
}

void WaysToSum(int L)
{
	int maxPossibliities = L * 9 + 1;
	int* possibilities = new int[maxPossibliities]();
	char* digits = new char[L]();
	digits[L - 1] = -1;
	int sum = 0;
	int upperLimit = 0;
	for (int i = 0; i < L; i++)
		upperLimit += (int)pow(10, i) * 9;


	for (int i = 0; i <= upperLimit; i++)
	{
		Iterate(digits, L);
		sum = SumDigits(digits, L);
		possibilities[sum]++;
	}

	cout << "When L = " << L << endl;
	PrintSumsOfN(possibilities, maxPossibliities);
	
	delete possibilities;
	delete digits;
}



//Template function set to run on each
//line read from the text file.
void LuckyCount(int n)
{
	int luckyCount = 0;
	stringstream ss;
	string digits;
	int mid = n / 2;

	for (int i = 0; i < n; i++)
		ss << '\0';

	digits = ss.str();

	ss.str("");


	for (int i = 0; i < n; i++)
		ss << '9';

	int attempts = atoi(ss.str().c_str());
	//unsigned long long attempts = strtoull(ss.str().c_str(), NULL, 10);

	for (int i = 0; i <= attempts; i++)
	//for (unsigned long long i = 0; i <= attempts; i++)
	{
		if (IsLucky(digits, mid)) luckyCount++;
		Iterate(digits);
	}

	cout << luckyCount << endl;
}


vector<string> GetLuckies()
{
	vector<string> luckyArr =
	{
		"0",
		"10",
		"670",
		"55252",
		"4816030",
		"432457640",
		"39581170420",
		"3671331273480",
		"343900019857310",
		"32458256583753952",
		"3081918923741896840",
		"294056694657804068000",
		"28170312778225750242100",
		"2707859169387181467852100",
		"261046730157780861858821136",
		"25228791861003454642059261392",
		"2443553412892220489195278947230",
		"237126779700111728623210793896700",
		"23050391247812238203687824747157800",
		"2244066255357188250744344225634235600",
		"218768894829904122626725603838896148680",
		"21353575263502884630388273714197145182600",
		"2086610157206763614866736016835099941514800",
		"204105559167234718098196864419783302549632800",
		"19983598742087310057357815311872236715171970100",
		"1958235988893910037740658552689739094876481545140",
		"192043570409723719873997281482556737440155994069900",
		"18847430845804472530652413091697822872821444349147800",
		"1850969282556229733639327066252630957954651870505893968",
		"181894832005057034383999852869437328659060112416355888580",
		"17885336470694891279287104747395798264488027368907029555640",
		"1759595312376617572854059903364131713003363235732517504574240",
		"173201762205643166279968008940412331699470273735812696599774110",
		"17056971894934558688846441987433052988620303403449436294441959820",
		"1680541301718359604648576749737521003907285387827431001567574176596",
		"165646654319976723701992406615067655308208865219762876621727020294840",
		"16333976304699214718657221877442624229398621392350520803192093730809000",
		"1611266420446186900661455564918186756941611539777885816296938086322793400",
		"159001106265949634483960692567311589105760040472435056876279269251280262400",
		"15695752713441211517384309707116838588162950015054857902560999394638257318080",
		"1549907697862929680336583303564541550920867807532198717258856653744296207074760",
		"153096138752277110214836722220881087457063409672964274344894548977869525514285400",
		"15126933076887535241547078349055723957328538056942697111947324195746641221987741240",
		"1495063936394820145978173084952651226318895610169643711778698526582132897696194675360",
		"147803690249353793831835578756919945270648840422121798343465830237679031761117155521520",
		"14615786698841561369944959191566195353879505580317403926959872129388565881505390562968052",
		"1445658259577075287740895176423089081604032456789033769154490620014797374846744269788548840",
		"143024700435101183997266162498015519369139255434050832382762644794442460391496029666811987520",
		"14153183315801667166858772596125134421835467308472191612483110921724154905563283000857391746100",
		"1400847570487018446424152137399824237820256780329223966658770240584725100387355667521375484520200",
		"138681178063913146486663255108385891670476531416644888545033078503482282975641730091720919340564340"
	};

	return luckyArr;
}


int main(int argc, char* argv[])
{
	if (argc == 1) { cout << "No file\n" << endl; return 0; }

	string line;
	ifstream file(argv[1]);
	vector<string> luckyArr = GetLuckies();

	if (file.is_open())
	{
		while (getline(file, line))
		{
			int n = atoi(line.c_str());
			n /= 2;
			cout << luckyArr[n] << endl;
		}
	}
	else
	{
		cout << "Unable to open file.\n";
	}
	file.close();


	return 0;
}
