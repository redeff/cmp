#include <bits/stdc++.h>
using namespace std;


bool is_local_low(int i, vector<pair<int, int>>& neigh, vector<int>& nums) {
  return nums[neigh[i].first] >= nums[i] && nums[neigh[i].second] >= nums[i];
}

class Solution {
public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    if(nums.size() == 0) return {0};
    vector<pair<int, int>> neigh;
    vector<int> out;

    unordered_set<int> less_n;
    int n = nums.size();
    neigh.resize(n + 1);
    out.resize(n - k + 1);

    nums.push_back(9999999);

    for(int i = 0; i < n; ++i) {
      neigh[i].first = i - 1;
      neigh[i].second = i + 1;
    }

    neigh[0].first = n;
    neigh[n - 1].second = n;
    neigh[n].second = 0;
    neigh[n].first = n - 1;

    for(int i = 0; i < n; ++i) {
      if(is_local_low(i, neigh, nums)) {
        less_n.insert(i);
      }
    }

    while(!less_n.empty()) {
      int l = *less_n.begin();
      if(l == n) break;
      cout << l << endl;
      for(int i = max((neigh[l].first == n) ? 0 : (neigh[l].first + 1), l - k + 1); i <= neigh[l].second - k; ++i) {
        cout << "lala";
        out[i] = nums[l];
        cout << out[i] << endl;
      }
      less_n.erase(less_n.begin());
      auto neighs = neigh[l];
      neigh[neighs.first].second = neighs.second;
      neigh[neighs.second].first = neighs.first;
      if(is_local_low(neigh[l].first, neigh, nums)) less_n.insert(neigh[l].first);
      if(is_local_low(neigh[l].second, neigh, nums)) less_n.insert(neigh[l].second);
    }

    return out;
  }
};

int main() {
  Solution s;
  vector<int> v = {1, 3, -1, -3, 5, 3, 6, 7};
  for(int i : s.maxSlidingWindow(v, 3)) {
    cout << i << " ";
  }
  return 0;
}
