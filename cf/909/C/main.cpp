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
  int n;
  cin >> n;
  auto chs = get_vector<char>((ll)n);

  vector<int> dp(n, 0);
  dp[0] = 1;
  for(int i = 0; i < n; ++i) {
    if(chs[i] == 'f') {
      for(int j = n - 1; j > 0; --j) {
        dp[j] = dp[j - 1];
      }
      dp[0] = 0;
    } else {
      int sum = 0;
      for(int j = n - 1; j >= 0; --j) {
        sum += dp[j];
        sum = sum % MOD;
        dp[j] = sum;
      }
    }
  }

  cout << dp[0] << endl;
}

