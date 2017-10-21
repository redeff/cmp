#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7

template <typename T>
void get_vector(ll size){
  vector<T> out;
  forn(sahdfjhfsk, 0, size){
    T temp;
    cin >> temp;
    out.push_back(temp);
  }
  return out;
}

int main(){
  int n;
  bool has_zeroes = true;
  for (int i = 0; i < 2 * n; ++i) {
    int tmp;
    cin >> tmp;
    has_zeroes = has_zeroes || tmp == 0;
  }

  cout << ((has_zeroes && n % 2 == 1) ? "Koyomi" : "Karen") << endl;

}
