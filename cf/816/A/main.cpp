#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7

bool palindrome(ll h, ll m){
  return h / 10 == m % 10 && h % 10 == m / 10;
}

int main(){
  ll h;
  ll m;
  cin >> h;
  {
    char c;
    cin >> c;
  }
  cin >> m;
  ll sleep = 0;
  while(!palindrome(h, m)){
    sleep++;
    m++;
    if(m == 60){
      m = 0;
      h++;
      if(h == 24){
        h = 0;
      }
    }
  }

  cout << sleep;

}
