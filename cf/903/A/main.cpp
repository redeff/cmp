#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7

template <typename T>
vector<T> get_vector(ll size){
  vector<T> out;
  forn(sahdfjhfsk, 0, size){
    T temp;
    cin >> temp;
    out.push_back(temp);
  }
  return out;
}

int main(){
  unordered_set<int> can;
  for(int a = 0; a < 22; ++a) {
    for(int b = 0; b < 22; ++b) {
      int total = a * 3 + b * 7;
      if(total < 21) {
        can.insert(total);
      }
    }
  }

  int n;
  cin >> n;
  forn(i, 0, n) {
    int x;
    cin >> x;
    if(x >= 21) cout << "YES";
    else if(can.count(x) > 0) cout << "YES";
    else cout << "NO";

    cout << endl;
  }
}

