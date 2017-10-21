#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7

int main(){
  ll n, k;
  cin >> n >> k;
  ll moves = n / k;
  if(moves % 2 == 1){
    cout << "YES";
  } else {
    cout << "NO";
  }

}
