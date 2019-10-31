// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 3
// Prime Palindrome

#include <sstream>
#include <iostream>
#include <string>
using namespace std;

int GetLargestPrimePalindrome(int under);
bool IsPalindrome(int number);
bool IsPrime(int number);
string ToString(int number);


int main(int argc, char* argv[])
{
	int under = 1000;
	cout << GetLargestPrimePalindrome(under);
	cout << endl;
	return 0;
}

int GetLargestPrimePalindrome(int under)
{
	int biggestPrimePalindrome = 0;
	for (int i = 11; i < under; i+=2)
		if (IsPrime(i) && IsPalindrome(i))
			biggestPrimePalindrome = i;
	return biggestPrimePalindrome;

}

bool IsPrime(int number)
{
	if (number % 3 == 0 || number % 2 == 0)
		return false;
	else
		for (int i = 5; i * i <= number; i += 6)
			if (number % i == 0 || number % (i + 2) == 0)
				return false;

	return true;
}

bool IsPalindrome(int number)
{
	string numStr = ToString(number);
	int front = 0;
	int back = numStr.length() - 1;

	while (back > front)
	{
		if (numStr[front] != numStr[back]) 
			return false;

		front++;
		back--;
	}

	return true;
}

string ToString(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}