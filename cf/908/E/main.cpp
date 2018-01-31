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

vector<vector<ll>> bell_trig = {{1}};
ll bell(ll n) {
  if(bell_trig.size() > n) return bell_trig[n][0];
  bell(n - 1);
  bell_trig.push_back({bell_trig.back().back()});
  for(ll i = 1; i <= n; ++i) {
    bell_trig.back().push_back((bell_trig[n][i - 1] + bell_trig[n - 1][i - 1]) % MOD);
  }
  return bell(n);
}

int main(){
  ll m, n;
  cin >> m >> n;

  vector<vector<bool>> ns;
  forn(i, 0, n) {
    string s;
    cin >> s;
    ns.emplace_back();
    for(char c : s) ns.back().push_back(c == '1');
  }

  // Partition of [0, m)
  vector<vector<ll>> primes {{}};
  for(ll i = 0; i < m; ++i) primes.back().push_back(i);

  for(vector<bool> &num : ns) {
    vector<vector<ll>> nprimes;

    for(vector<ll> &subset : primes) {
      nprimes.emplace_back();
      for(ll s : subset) if(num[s]) {
        nprimes.back().push_back(s);
      }
      if(nprimes.back().empty()) nprimes.pop_back();
      nprimes.emplace_back();
      for(ll s : subset) if(!num[s]) {
        nprimes.back().push_back(s);
      }
      if(nprimes.back().empty()) nprimes.pop_back();
    }

    swap(primes, nprimes);
  }

  ll total = 1;
  for(auto &p : primes) {
    total *= bell(p.size());
    total = total % MOD;
  }

  cout << total << endl;
}

