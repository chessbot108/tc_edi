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

string change(string s) {
    int len = s.length();
    int rlen = rand() % len;

    int cur = (int) s[rlen];
    int n = cur;

    while (cur == n) {
        n = rand() % 26 + 97;
    }

    s[rlen] = (char) n;

    return s;
}

int diff(string a, string b) {
    long long change = 0;
    long long idx = 0;
    if (a.length() != b.length()) {
        return 0;
    }
        
    
    while (idx < (long long) a.length()) {
        if (a[idx] != b[idx]) {
            change += 1;
        }
            
        idx += 1;
    }
    return change;
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
			string test_data = "";
			int T = 0;

			if (i == 1) //sample case
				test_data = "2\n4\nWater Lemonade Punch Juice\nMelium Wader\n2\nCoffee Tea\nMediuf Tee";
			else if (i == 2 || i == 3) //easy tests
				T = rand() % 46 + 5;
			else if (i == 8 || i == 10) //hardest
				T = MAXN;
			else //pretty hard
				T = rand() % 501 + 500;

			if (i != 1)
			{
				test_data += to_string(T) + "\n";
				for (int j = 0; j < T; j++)
				{
                    int a = rand() % 100 + 1;
                    int size = rand() % 3;
                    vector<string> ar;
                    int chosenone = rand() % a;
                    string rsize = "";
                    string rchosenone = "";
					test_data += to_string(a) + "\n";

                    if (size == 0) {
                        rsize = "small";
                    } else if (size == 1) {
                        rsize = "medium";
                    } else {
                        rsize = "large";
                    }
					
                    for (int k = 0; k < a; k++) {
                        string rword = randword();
                        
                        if (ar.size() > 0) {

                            while (true) {
                                rword = randword();
                                bool done = true;
                                for (string s: ar) {
                                    if (diff(s, rword) == 1 || diff(s, rword) == 2 || diff(s, rword) == 3) {
                                        done = false;
                                        break;
                                    }
                                }

                                if (done == true) {
                                    break;
                                }
                            }
                        }

                        ar.push_back(rword);


                        test_data += rword;
                        if (k == chosenone) {
                            rchosenone = rword;
                        }

                        if (k != a - 1) {
                            test_data += " ";
                        } else {
                            test_data += "\n";
                        }
                    }
                    rsize = change(rsize);
                    rchosenone = change(rchosenone);
                    test_data += rsize + " " + rchosenone + "\n";


				}
			}

			cout << test_data << "\n";
			cout.close();
		}
	}
	return 0;
}
