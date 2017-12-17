#include <bits/stdc++.h>
using namespace std;

int main(){
  int n;
  cin >> n;
  vector<int> ns;
  for(int i = 0; i < n; ++i) {
    ns.emplace_back();
    cin >> ns.back();
    int tmp;
    cin >> tmp;
  }

  partial_sort(ns.begin(), xs.begin() + 2, xs.end());
  int mn = ns[1];
  partial_sort(ns.begin(), xs.begin() + 2, xs.end(), greater<int>{});
  int mx = ns[1];

  if(mx < 0 || mn > 0) {
    cout << "Yes";
  } else {
    cout << "No";
  }

}

int main(int a, int b) {

}
