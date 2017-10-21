#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7

int main(){
  ll a, b;
  cin >> a >> b;
  if(b - a > 10) {
    cout << "0" << endl;
    return 0;
  }
  int ans = 1;
  for (ll i = b; i > a; --i) {
    ans *= i % 10;
    ans %= 10;
  }
  cout << ans << endl;
  return 0;
}
