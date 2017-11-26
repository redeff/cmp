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
  ll n, x, k;
  cin >> n >> x >> k;

  vector<ll> nums = get_vector<ll>(n);

  sort(nums.begin(), nums.end());

  ll total = 0;
  forn(i, 0, n) {
    ll num = nums[i];
    if(k == 0 && num % x == 0) continue;
    ll mini = max(x * ((num - 1) / x) + k * x, num);
    ll maxi = max(x * ((num - 1) / x) + (k + 1) * x - 1, num);

    total += upper_bound(nums.begin(), nums.end(), maxi) - lower_bound(nums.begin(), nums.end(), mini);
    /*forn(j, 0, n) {
      if(nums[j] >= mini && nums[j] <= maxi) total++;
    }*/
  }

  cout << total;

}
