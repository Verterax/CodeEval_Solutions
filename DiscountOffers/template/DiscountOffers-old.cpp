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
		ss = (double)GetVowelCount(person) * 1.5;
	}
	else
	{
		ss = (double)GetConsonantCount(person);
	}

	if (SharedFactors(lettersInPerson, lettersInProduct) != 1)
		ss *= 1.5;

	return ss;
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
	int timeout = 0;

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

		timeout++;
		if (timeout > 20)
		{
			//cout << "Timeout Get Assignments" << endl;
			break;
		}
	}


	return assignments;
}

double GetSum(vector<vector<double>> peopleProducts, vector<pair<int, int>> assignments)
{
	double sum = 0;
	int size = assignments.size();
	bool printTable = false;

	for (int i = 0; i < size; ++i)
	{
		sum += peopleProducts[assignments[i].first][assignments[i].second];
		peopleProducts[assignments[i].first][assignments[i].second] = -1;
	}

	return sum;
}

vector<pair<int, int>> GetCoverings(vector<vector<double>> peopleProducts, int size)
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

	if (tokens.size() != 2)
	{
		std::cout << "0.00";
		return;
	}

	vector<string> people = GetTokens(tokens[0], ',');
	vector<string> products = GetTokens(tokens[1], ',');
	vector<vector<double>> peopleProducts(people.size(), vector<double>(products.size()));
	vector<vector<double>> tableCopy(people.size(), vector<double>(products.size()));
	vector<pair<int, int>> coverings;
	static const double maxDouble = 1000000;
	double min, ss, sum, maxSS = 0;
	int x, y, i, vote, linesDrawn = 0;
	int size = people.size();
	int timeout = 0;


	//Base cases (0 products or people)
	if (people.size() == 0 || products.size() == 0)
	{
		std::cout << "0.00";
		return;
	}

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

	//Add people to made equal with products.
	while (products.size() > people.size())
	{
		people.push_back("Dummy Person");
		vector<double> person(products.size());
		for (x = 0; x < products.size(); ++x)
			person[x] = maxSS;
		peopleProducts.push_back(person);
		for (x = 0; x < products.size(); ++x)
			person[x] = 0;
		tableCopy.push_back(person);
	}

	//If more people than products, add dummy item
	while (people.size() > products.size())
	{
		products.push_back("Dummy Item");
		for (y = 0; y < people.size(); ++y)
		{
			peopleProducts[y].push_back(maxSS);
			tableCopy[y].push_back(0);
		}
	}

	if (products.size() > people.size())
	{
		cout << "uh" << endl;
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

#pragma endregion

	coverings = GetCoverings(peopleProducts, size);
	while (coverings.size() < size)
	{
		Refine(peopleProducts, coverings, size);
		coverings = GetCoverings(peopleProducts, size);
		timeout++;

		if (timeout == 20)
		{
			//cout << "Timeout refine coverings" << endl;
			break;
		}
	}

	vector<pair<int, int>> assignments = GetAssignments(peopleProducts, people.size());

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


