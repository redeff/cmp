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

vector<ll> divs;
unordered_map<ll, ll> dp;

ll pow_2(ll n) {
  if(n == 0) return 1;
  else if (n % 2 == 1) {
    ll rec = pow_2(n / 2);
    return (2 * rec * rec) % MOD;
  } else {
    ll rec = pow_2(n / 2);
    return (rec * rec) % MOD;
  }
}

ll part(ll n) {
  return pow_2(n - 1);
}

ll calculate(ll y) {
  vector<ll> primes;
  ll t = y;
  for(ll i = 2; i <= t; ++i) {
    if(t % i == 0) {
      primes.push_back(i);
      while(t % i == 0) t /= i;
    }
    if(i * i > t && t != 1){
      primes.push_back(t);
      break; 
    }
  }

  ll total = 0;
  for(unsigned long long i = 0; i < (1 << primes.size()); ++i) {
    ll prod = 1;
    bool even = false;
    for(int j = 0; j < primes.size(); ++j) {
      if(i & (1 << j)) {
        prod *= primes[j];
        even = !even;
      }
    }

    total += part(y / prod) * (even ? -1 : 1);
    total %= MOD;
  }
  total += MOD;
  total %= MOD;

  return total;
}


int main(){
  int x, y;
  cin >> x >> y;
  if(y % x != 0) {
    cout << 0 << endl;
  } else {
    cout << calculate(y / x) << endl;
  }
}

