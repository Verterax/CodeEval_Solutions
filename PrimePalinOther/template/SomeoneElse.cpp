#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
bool isPalindrom(int N) {
	vector<int> v, v_reverse;
	while (N) {
		v.push_back(N % 10);
		N /= 10;
	}
	v_reverse = v;
	reverse(v_reverse.begin(), v_reverse.end());
	return v == v_reverse;
}
int main(int argc, char* argv[]) {
	ifstream file;
	file.open(argv[1]);
	string lineBuffer;
	while (!file.eof()) {
		getline(file, lineBuffer);
		if (lineBuffer.length() == 0)
			continue; //ignore all empty lines
		else {
			istringstream iss(lineBuffer);
			int L, R, res = 0;
			iss >> L >> R;
			//prepare-get all palindrom in the range of [L,R]
			for (int i = L; i <= R; i++) { //start point of subrange
				for (int j = i; j <= R; j++) { //end point of subrange
					int sum = 0;
					for (int k = i; k <= j; k++) {
						if (isPalindrom(k)) {
							++sum;
						}
					}
					if (sum % 2 == 0)
						++res;
				}
			}
			cout << res << endl;
		}
	}
	return 0;
}
