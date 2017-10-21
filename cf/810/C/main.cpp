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
  ll n = 0;
  cin >> n;
  auto nums = get_vector<ll>(n);
  sort(nums.begin(), nums.end());

  ll pow2 = 1;
  ll low_sum = 0;
  ll big_sum = 0;
  ll total = 0;

  for(ll i = 0, j = n - 1; i < n; i++, j--){
    low_sum += nums[i] % MOD;
    big_sum += nums[j] % MOD;
    total += (pow2 * ((big_sum - low_sum) % MOD)) % MOD; 
    total %= MOD;
    pow2 = pow2 * 2 % MOD;
  }

  cout << total << endl;

}
