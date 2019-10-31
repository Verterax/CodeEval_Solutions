// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 48
// Discount Offers

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
#include <math.h>
#include <limits>
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
			if (line.size() > 0)
				lines.push_back(line);
		}
	}
	else
	{
		std::cout << "Unable to open file.\n";
	}
	file.close();

	return lines;
}

vector<string> GetTokens(string line, char delim)
{
	vector<string> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		tokens.push_back(token);
	}

	return tokens;
}

vector<int> GetInts(string line, char delim)
{
	vector<int> tokens;
	string token;
	stringstream stream(line);
	while (std::getline(stream, token, delim))
	{
		tokens.push_back(atoi(token.c_str()));
	}

	return tokens;
}

void RemChars(string& str, const char chars[], int charLen)
{
	int i;
	int strLen = str.size();
	string::iterator iter = str.begin();
	bool didErase = false;
	while (iter != str.end())
	{
		didErase = false;
		for (i = 0; i < charLen; i++)
			if ((*iter) == chars[i])
			{
				str.erase(iter);
				didErase = true;
				break;
			}
		if (!didErase) iter++;
	}
}


int GetLetterCount(string str)
{
	int count = 0;
	for (int i = 0; i < str.size(); ++i)
		if (isalpha(str[i])) ++count;

	return count;

}

bool IsVowel(char c)
{
	if (c < 'a') 
		c += 32;
	if (c == 'a')
		return true;
	else if (c == 'e')
		return true;
	else if (c == 'i')
		return true;
	else if (c == 'o')
		return true;
	else if (c == 'u')
		return true;
	else if (c == 'y')
		return true;
	else
		return false;
}

int GetVowelCount(string str)
{
	int count = 0;
	for (int i = 0; i < str.size(); ++i)
	{
		if (IsVowel(str[i]))
		{
			count++;
		}
	}

	return count;
}

int GetConsonantCount(string str)
{
	int count = 0;
	for (int i = 0; i < str.size(); ++i)
		if (isalpha(str[i]) && !IsVowel(str[i]))
			++count;

	return count;
}

int SharedFactors(int a, int b)
{
	int max = (a > b) ? a : b;
	if (a % 2 == 0 && b % 2 == 0)
		return 2;

	for (int i = 3; i <= max; i += 2)
		if (a % i == 0 && b % i == 0)
			return i;

	return 1;
}

double GetSS(string person, string product)
{
	double ss = 0.0;

	int lettersInProduct = GetLetterCount(product);
	int lettersInPerson = GetLetterCount(person);

	if (lettersInProduct % 2 == 0) // Even letters in
	{
		ss = (double)GetVowelCount(person);
		ss *= 1.5;
	}
	else
	{
		ss = (double)GetConsonantCount(person);
	}

	if (SharedFactors(lettersInPerson, lettersInProduct) != 1)
		ss *= 1.5;

	return ss;
}

void PrintFirstN(string str, int n, int wid)
{
	std::cout << setw(wid);
	for (int i = 0; i <= n && i < str.size(); ++i)
		std::cout << str[i];
}

void PrintTable(vector<vector<double>> peopleProducts, int size)
{
	int prec = 4;
	int wid = 8;
	int nChars = 4;

	std::cout << endl;
	for (int y = 0; y < size; ++y) //y = people
	{
		for (int x = 0; x < size; ++x) //x = products
		{
			std::cout << setprecision(prec) << std::setw(wid) << peopleProducts[y][x];
		}
		std::cout << endl;
	}

	std::cout << endl;
}

void PrintTable(vector<string> people, vector<string> products, vector<vector<double>> peopleProducts, vector<int> peopleZeros, vector<int> productZeros)
{
	int prec = 4;
	int wid = 8;
	int nChars = 4;

	std::cout << setw(5) << "";
	for (int i = 0; i < products.size(); ++i)
	{
		PrintFirstN(products[i], nChars, 4);
	}
	PrintFirstN("Zeros:", nChars, 4);
	std::cout << endl;

	for (int y = 0; y < people.size(); ++y) //y = people
	{
		PrintFirstN(people[y], nChars, 0);
		for (int x = 0; x < products.size(); ++x) //x = products
		{
			std::cout << setprecision(prec) << std::setw(wid) << peopleProducts[y][x];
		}
		std::cout << std::setw(wid) << peopleZeros[y];
		std::cout << endl;
	}

	std::cout << endl;
	PrintFirstN("Zeros:", nChars, 0);
	for (int x = 0; x < people.size(); ++x)
	{
		std::cout << std::setw(wid) << productZeros[x];
	}

	std::cout << endl;
}

void SterilizePlus(vector<vector<double>>& peopleProducts, pair<int, int> assign, int size)
{
	//Sterilize row
	for (int x = 0; x < size; ++x)
		if (peopleProducts[assign.first][x] == 0)
			peopleProducts[assign.first][x] = -1;

	//Sterilze column
	for (int y = 0; y < size; ++y)
		if (peopleProducts[y][assign.second] == 0)
			peopleProducts[y][assign.second] = -1;

	peopleProducts[assign.first][assign.second] = -2;
}

vector<pair<int, int>> GetAssignments(vector<vector<double>> peopleProducts, int size)
{
	vector<pair<int, int>> assignments;
	int x, y, zeroCount, assignAt;
	bool didAssign = false;
	int minAssign = 1;

	bool printTable = false;

	if (printTable)
	{
		PrintTable(peopleProducts, size);
		std::cout << endl;
	}

	while (assignments.size() < size)
	{
		didAssign = false;
		//Assign all rows.
		for (y = 0; y < size; ++y)
		{
			zeroCount = 0; // Count zeros
			assignAt = -1;
			for (x = 0; x < size; ++x)
			{
				if (peopleProducts[y][x] == 0)
				{
					zeroCount++;
					assignAt = x;
				}
			}

			if (zeroCount == minAssign)
			{
				pair<int, int> assign(y, assignAt);
				assignments.push_back(assign);
				didAssign = true;
				SterilizePlus(peopleProducts, assign, size);

				if (printTable)
				{
					PrintTable(peopleProducts, size);
					std::cout << "Assignment in row " << assign.first << ", " << assign.second << endl;
					std::cout << endl;
				}
			}
		}

		//Assign all columns.
		for (x = 0; x < size; ++x)
		{
			zeroCount = 0; // Count zeros
			assignAt = -1;
			for (y = 0; y < size; ++y)
			{
				if (peopleProducts[y][x] == 0)
				{
					zeroCount++;
					assignAt = y;
				}
			}

			if (zeroCount == minAssign)
			{
				pair<int, int> assign(assignAt, x);
				assignments.push_back(assign);
				didAssign = true;
				SterilizePlus(peopleProducts, assign, size);

				if (printTable)
				{
					PrintTable(peopleProducts, size);
					std::cout << "Assignment in column " << assign.first << ", " << assign.second << endl;
					std::cout << endl;
				}
			}
		}

		if (didAssign)
		{
			minAssign = 1;
		}
		else
		{
			if (minAssign == size + 1) break;
			minAssign++;
		}

	}


	return assignments;
}

double GetSum(vector<vector<double>> peopleProducts, vector<pair<int, int>> assignments)
{
	double sum = 0;
	int size = assignments.size();
	bool printTable = false;

	//system("cls");

	for (int i = 0; i < size; ++i)
	{
		if (printTable)
		{
			std::cout << "Before" << endl;
			PrintTable(peopleProducts, size);
			std::cout << endl;
		}

		sum += peopleProducts[assignments[i].first][assignments[i].second];
		peopleProducts[assignments[i].first][assignments[i].second] = -1;

		if (printTable) {
			std::cout << "After: " << i << endl;
			PrintTable(peopleProducts, size);
			std::cout << endl;
			system("cls");
		}
	}

	return sum;
}

vector<pair<int, int>> GetCoverings(vector<string> people, vector<string> products, vector<vector<double>> peopleProducts, int size)
{
	vector<pair<int, int>> coverings;
	vector<int> rowZeros(size);
	vector<int> colZeros(size);
	int x, y, i;
	int zeroCount;
	bool isRow = true;
	int index = 0;

	for (y = 0; y < size; ++y) { 
		for (x = 0; x < size; ++x) {
			if (peopleProducts[y][x] == 0) {
				rowZeros[y]++;
				colZeros[x]++;
			}
		}
	}

	//PrintTable(people, products, peopleProducts, rowZeros, colZeros);
	//std::cout << endl;

	while (true)
	{
		zeroCount = 0;
		for (y = 0; y < size; ++y) { 
			if (rowZeros[y] > zeroCount) {
				isRow = true;
				zeroCount = rowZeros[y];
				index = y;				
			}
		}
		
		for (x = 0; x < size; ++x) { 
			if (colZeros[x] > zeroCount) {
				isRow = false;
				zeroCount = colZeros[x];
				index = x;
			}
		}

		if (zeroCount == 0) {
			break;
		}
		else {
			//decrement zeros from other counts.
			//add cover to list.
			if (isRow) { // 
				rowZeros[index] = 0;
				for (i = 0; i < size; ++i)
					if (peopleProducts[index][i] == 0)
						colZeros[i]--;
				pair<int, int> cover(index, -1);
				coverings.push_back(cover);
			} else {
				colZeros[index] = 0;
				for (i = 0; i < size; ++i)
					if (peopleProducts[i][index] == 0)
						rowZeros[i]--;
				pair<int, int> cover(-1, index);
				coverings.push_back(cover);
			}
		}

		//PrintTable(people, products, peopleProducts, rowZeros, colZeros);
		//std::cout << endl;
	}

	return coverings;
}

//Refine matrix to expose new covering.
void Refine(vector<vector<double>> &peopleProducts, vector<pair<int, int>> coverings, int size)
{
	vector<int> rowCovers(size);
	vector<int> colCovers(size);
	double theta = 1000000;
	int x, y;
	
	//Init row and col covers.
	for (int i = 0; i < coverings.size(); ++i)
		if (coverings[i].first != -1)
			rowCovers[coverings[i].first] = 1;
		else
			colCovers[coverings[i].second] = 1;

	//Find theta
	for (y = 0; y < size; ++y)
		for (x = 0; x < size; ++x)
			if (rowCovers[y] == 0 && colCovers[x] == 0 && peopleProducts[y][x] != 0 && peopleProducts[y][x] < theta)
				theta = peopleProducts[y][x];

	//Subtract theta from uncovered edges
	for (y = 0; y < size; ++y)
		for (x = 0; x < size; ++x)
			if (rowCovers[y] == 0 && colCovers[x] == 0 && peopleProducts[y][x] != 0)
				peopleProducts[y][x] -= theta;
			else if (rowCovers[y] == 1 && colCovers[x] == 1)
				peopleProducts[y][x] += theta;
}

void DiscountOffers(string line)
{
	//Code goes here.
	bool printTables = false;
	vector<string> tokens = GetTokens(line, ';');
	vector<string> people = GetTokens(tokens[0], ',');
	vector<string> products = GetTokens(tokens[1], ',');
	vector<vector<double>> peopleProducts(people.size(), vector<double>(products.size()));
	vector<vector<double>> tableCopy(people.size(), vector<double>(products.size()));
	vector<pair<int, int>> coverings;
	static const double maxDouble = 1000000;
	double min, ss, sum, maxSS = 0;
	int x, y, i, vote, linesDrawn = 0;
	int size = people.size();

#pragma region Init Table

	//Assign SS to table. Get MaxSS
	for (y = 0; y < people.size(); ++y) //y = people
		for (x = 0; x < products.size(); ++x) //x = products
		{
			tableCopy[y][x] = peopleProducts[y][x] = ss = GetSS(people[y], products[x]);
			if (ss > maxSS) maxSS = ss;
		}

	//Subtract Max, leave absolute.
	for (y = 0; y < people.size(); ++y) //y = people
		for (x = 0; x < products.size(); ++x) //x = products
		{
			peopleProducts[y][x] = abs(peopleProducts[y][x] - maxSS);
		}


	//If more people than products, add dummy item
	if (people.size() > products.size())
	{
		products.push_back("Dummy Item");
		for (y = 0; y < people.size(); ++y)
		{
			peopleProducts[y].push_back(maxSS);
			tableCopy[y].push_back(0);
		}
	}

	vector<int> peopleZeros; // y  (zero count, line drawn)
	vector<int> productZeros; // x (zero count, line drawn)
	sum = 0;
	vote = linesDrawn = 0;
	min = maxDouble;
	peopleZeros.clear();
	peopleZeros.resize(people.size());
	productZeros.clear();
	productZeros.resize(products.size());

	if (printTables)
	{
		PrintTable(people, products, peopleProducts, peopleZeros, productZeros);
		std::cout << "Tables squred and inverted." << endl;
		std::cout << endl;
	}

	for (y = 0; y < people.size(); ++y) //y = people
	{
		for (i = 0; i < 2; ++i) //Rows and col. Find min on first pass.
		{
			if (i == 0) min = maxDouble;
			for (x = 0; x < products.size(); ++x) //x = products
			{
				if (i == 0) // Get min for row.
				{
					if (peopleProducts[y][x] < min)
						min = peopleProducts[y][x];
				}
				else
				{
					peopleProducts[y][x] -= min;
				}
			}
		}
	}

	if (printTables)
	{
		PrintTable(people, products, peopleProducts, peopleZeros, productZeros);
		std::cout << "Row mins subtacted." << endl;
		std::cout << endl;
	}

	for (y = 0; y < people.size(); ++y) //y = people
	{
		for (i = 0; i < 2; ++i) //Rows and col. Find min on first pass.
		{
			if (i == 0) min = maxDouble;
			for (x = 0; x < products.size(); ++x) //x = products
			{
				if (i == 0) // Get min for row.
				{
					if (peopleProducts[x][y] < min)
						min = peopleProducts[x][y];
				}
				else
				{
					peopleProducts[x][y] -= min;
				}
			}
		}
	}

	if (printTables)
	{
		PrintTable(people, products, peopleProducts, peopleZeros, productZeros);
		std::cout << "Column Mins subtracted. Zeros per row col counted." << endl;
		std::cout << endl;
	}

#pragma endregion

	coverings = GetCoverings(people, products, peopleProducts, size);
	while (coverings.size() < size)
	{
		Refine(peopleProducts, coverings, size);
		if (printTables)
		{
			PrintTable(people, products, peopleProducts, peopleZeros, productZeros);
			std::cout << "The Table has been refined.." << endl;
			std::cout << endl;
		}
		coverings = GetCoverings(people, products, peopleProducts, size);
	}

	vector<pair<int, int>> assignments = GetAssignments(peopleProducts, people.size());

	if (printTables)
		PrintTable(people, products, peopleProducts, peopleZeros, productZeros);

	double result = GetSum(tableCopy, assignments);
	std::cout << std::fixed << std::setprecision(2) << result;
}

int main(int argc, char* argv[])
{
	if (argc == 1) { std::cout << "No file\n" << endl; return 0; }
	vector<string> lines = GetLines(argv[1]);
	int lineCount = lines.size();
	if (lineCount == 0) { std::cout << "No lines\n"; return 0; }

	for (int i = 0; i < lineCount; i++)
	{
		//Evaluate lines.
		DiscountOffers(lines[i]);
		std::cout << endl;
	}


	return 0;
}

#pragma endregion