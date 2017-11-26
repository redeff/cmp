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
  ll n;
  cin >> n;
  vector<int> angles = get_vector<int>(n);

  vector<int> sums;
  sums.push_back(0);
  forn(i, 0, n) {
    sums.push_back(sums.back() + angles[i]);
  }

  int mini = 99999999;
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      mini = min(mini, abs(180 - (sums[i] - sums[j])));
    }
  }

  cout << 2 * mini;

}
