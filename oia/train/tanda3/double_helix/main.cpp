#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, n) for(int i = 0; i < int(n); ++i)

vector<int> get_vector(int n) {
  vector<int> out;
  forn(i, n) {
    out.emplace_back();
    cin >> out.back();
  }
  return out;
}

vector<int> sums(vector<int> vs) {
  vector<int> s = {0};
  for(auto v : vs) {
    s.push_back(s.back() + v);
  }
  return s;
}

void testcase(int a) {
  auto as = get_vector(a);
  int b;
  cin >> b;
  auto bs = get_vector(b);

  int i = 0;
  int j = 0;
  vector<pair<int, int>> com = {{-1, -1}};

  while(i < a && j < b) {
    if(as[i] == bs[j]) {
      com.emplace_back(i, j);
      i++;
      j++;
    } else if(as[i] < bs[j]) i++;
    else j++;
  }

  com.emplace_back(a, b);

  vector<int> asum = sums(as);
  vector<int> bsum = sums(bs);

  ll best_sum = 0;
  for(int k = 1; k < int(com.size()); ++k) {
    best_sum += max(asum[com[k].first] - asum[com[k - 1].first + 1], bsum[com[k].second] - bsum[com[k - 1].second + 1]);
    if(k != int(com.size()) - 1) {
      best_sum += as[com[k].first];
    }
  }
  cout << best_sum << endl;
}

int main() {
  int t;
  while(true) {
    cin >> t;
    if(t == 0) break;
    testcase(t);
  }
}
