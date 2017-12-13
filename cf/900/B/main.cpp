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
  int a, b, c;
  cin >> a >> b >> c;

  unordered_set<int> used;
  int x = a;
  int pos = 0;
  used.insert(x);
  while(true) {
    pos++;
    x = x * 10;
    int digit = x / b;
    x = x % b;
    if(digit == c) {
      cout << pos << endl;
      return 0;
    }
    if(used.count(x) > 0) break;
    used.insert(x);
  }

  cout << -1 << endl;
  return 0;
}

