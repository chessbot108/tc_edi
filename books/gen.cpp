#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
#define NUM_TESTS 10
#define MAXN 1000
/*
* first 3 cases pretty easy
* next 7
*/

string randword() {
    int randlen = rand() % 10 + 3;
    string res = "";

    for (int i = 0; i < randlen; i++) {
        int ascii = rand() % 26 + 97;
        res += (char) ascii;
    }

    return res;
}

int main()
{
	ofstream cout;
	string format = ".in";
	srand(time(NULL));

	for (int i = 1; i <= NUM_TESTS; i++)
	{
		cout.open(to_string(i) + format);

		if (cout)
		{
			vector<int> ar;
			string test_data = "";
			int T = 0;

			if (i == 1) //sample case
				test_data = "4\nharry 1987\norange 1776\nhotels 1973\nmoon 2018";
			else if (i == 2 || i == 3) //easy tests
				T = rand() % 46 + 5;
            else if (i == 4 || i == 5)
                T = rand() % 250 + 251;
			else if (i == 8 || i == 10) //hardest
				T = MAXN;
			else //pretty hard
				T = rand() % 500 + 501;

			if (i != 1)
			{
				test_data += to_string(T) + "\n";
				for (int j = 0; j < T; j++)
				{
					int num = rand() % 10000;

					if (ar.size() >= 1) {
						bool done = true;
						while (true) {
							done = true;
							num = rand() % 10000;
							for (int n: ar) {
								
								if (num == n) {
									done = false;
									break;
								}
							}

							if (done == true) {
								break;
							}
						}
						
							
					}
					
					ar.push_back(num);
					
					test_data += randword() + " " + to_string(num) + "\n";
				}
			}

			cout << test_data << "\n";
			cout.close();
		}
	}
	return 0;
}
