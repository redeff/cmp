#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
  while(true){
    ll n;
    cin >> n;
    if(n == -1) break;
    n--;
    vector<ll> nums;

    for(ll i = 0; i < n; ++i){
      nums.emplace_back();
      cin >> nums.back();
    }

    sort(nums.begin(), nums.end());
    ll hi = nums[n / 2];
    ll lo = nums[n / 2 - 1];

    ll sum = 0;
    for(auto n : nums){
      sum += n;
    }

    int result = 0;
    if(sum >= n * lo && !binary_search(nums.begin(), nums.end(), (n + 1) * lo - sum)) result++;
    if(sum <= n * hi && !binary_search(nums.begin(), nums.end(), (n + 1) * hi - sum)) result++;
    if(sum < n * hi && sum > n * lo && sum % n == 0) result++;
    cout << result << endl;
  }
}
