#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
  ll n, m, a, d;
  vector<ll> nums;
  cin >> n >> m >> a >> d;

  for(int i = 0; i < m; ++i) {
    ll t;
    cin >> t;
    nums.push_back(t);
  }

  ll total = 0;
  ll bound = -1;
  ll last = 1;
  ll stride = d / a + 1;
  for(int i = 0; i < nums.size(); ++i) {
    if((bound / a) * a + 1 < nums[i]) {
      ll low, upp;
      low = bound + 1;
      upp = min(nums[i], d * a);

      ll am = upp / a - (low - 1) / a;
      ll fir = (low - 1) / a + 1;

      total += (am - 1) / stride + 1;
      ll last = ((am - 1) / stride) * stride;
      bound = last + d;
    }

    if(bound < nums[i]) {
      bound = nums[i] + d;
      total++;
    }
  }

      ll low, upp;
      low = nums.back() + 1;
      upp = n * a + 1;

      if(low <= upp) {

      ll am = upp / a - (low - 1) / a;
      ll fir = (low - 1) / a + 1;

      total += (am - 1) / stride + 1;
      ll last = ((am - 1) / stride) * stride;
      bound = last + d;
      }

  cout << total;
}
