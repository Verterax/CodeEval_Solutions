// By Christopher Caldwell
// chris@codehadouken.com
// Challenge 4
// Sum Of Primes

#include <iostream>
using namespace std;

int SumOfFirstNPrimes(int n);
bool IsPrime(int number);


int main(int argc, char* argv[])
{
	int n = 1000;
	cout << SumOfFirstNPrimes(n);
	cout << endl;
	return 0;
}

int SumOfFirstNPrimes(int n)
{	
	int sum = 2;
	int gotPrimes = 1;
	int i = 3;
	while (true)
	{
		if (IsPrime(i))
		{
			gotPrimes++;
			sum += i;

			if (gotPrimes == n)
				break;
		}

		i += 2;
	}
	return sum;
}

bool IsPrime(int number)
{
	if (number <= 3)
		return number > 1;
	if (number % 3 == 0 || number % 2 == 0)
		return false;
	else
		for (int i = 5; i * i <= number; i += 6)
			if (number % i == 0 || number % (i + 2) == 0)
				return false;

	return true;
}

