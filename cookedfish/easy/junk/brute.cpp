
#include <iostream>
using namespace std;

int main() {
  int Q;
  cin >> Q;
  
  for (int q = 0; q < Q; q++)
  {
    int n, k;
    cin >> n >> k;
    
    int bind = 1;
    int eind = 1;
    int ans = 0;
    bool solved = false;
    while (ans != n)
    {
      if (ans < n) ans += eind++;
      else ans -= bind++;
      
      if (eind > n) break;
      
      if (ans == n) 
      {
        solved = true;
        cout << bind << " " << eind << "\n";
      }
    }
    
    if (solved) continue;
    else cout << -1 << " " << -1 << "\n";
  }
  return 0;
}
