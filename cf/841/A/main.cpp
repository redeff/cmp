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
  vector<ll> app(26);
  ll n, k;
  cin >> n >> k;
  forn(lakshf, 0, n){
    char tmp;
    cin >> tmp;
    app[tmp - 'a']++;
    if(app[tmp - 'a'] > k){
      cout << "NO";
      return 0;
    }
  }
  cout << "YES";
}
