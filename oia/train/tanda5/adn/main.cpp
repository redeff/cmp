#include <bits/stdc++.h>
using namespace std;

const int INF = 333333;

#define cin ifs
#define cout ofs


int main() {
  ifstream ifs("adn.in");
  ofstream ofs("adn.out");
  int n(0), m(0), k(0);
  cin >> n >> m >> k;

  string ns, ms;
  cin >> ns >> ms;

  if(n > m) {
    swap(n, m);
    swap(ns, ms);
  }

  if(m - n > k) {
    cout << "Muy distintas." << endl;
    return 0;
  }

  // dp[a][b] = edit_distance(ns[0:a], ms[0:b])
  // vector<vector<int>> dp;

  /*
  for(int j = 0; j < m; ++j) {
    for(int i = 0; i < n; ++i) {
      int add_n;
      if(dp[])
      int add_m;
      int mod;
      dp[i][j] = min()
    }
  }
  */
  /*
  for(int i = 0; i < k; ++i) {
    dp[0][i] = i;
  }

  for(int x = 1; x <= n; ++x) {
    for(int y = max(0, x - k - 1); y < x + k + 1; ++y) {
      int add_n;
      try {
        add_n = dp.at(x - 1).at(y) + 1;
      } catch (out_of_range) {
        add_n = INF;
      }

      int add_m;
      try {
        add_m = dp.at(x).at(y - 1) + 1;
      } catch (out_of_range) {
        add_m = INF;
      }

      int mod;
      try {
        mod = dp.at(x - 1).at(y - 1) + ((ns.at(x - 1) == ms.at(y - 1)) ? 0 : 1);
      } catch (out_of_range) {
        mod = INF;
      }

      dp[x][y] = min(min(add_n, add_m), mod);
    }
    dp.erase(x - 1);
  }
  */

  int size = 2 * k + 1;
  vector<int> a(size, INF);

  vector<int> b(size, INF);
  
  vector<int> * dp = &a;
  vector<int> * new_dp = &b;

  for(int i = 0; i <= k; ++i) {
    (*dp)[k + i] = i;
  }

  for(int x = 0; x < n; ++x) {
    // dp[k] represents edit_distance(ns[:x], ms[:x])
    // dp[i] represents edit_distance(ns[:x-k+i], ms[:x])
    for(int i = 0; i < size; ++i) {
      // We're looking at entry (x, i - k + x)
      int add_n;
      if(i + 1 < 0 || i + 1 >= size) {
        add_n = INF;
      } else {
        add_n = (*dp)[i + 1] + 1;
      }

      int add_m;
      if(i - 1 < 0 || i - 1 >= size) {
        add_m = INF;
      } else {
        add_m = (*new_dp)[i - 1] + 1;
      }

      int mod;
      if(i >= size || i < 0 || x >= n || x < 0 || i + x - k >= m || i + x - k < 0) {
        mod = INF;
      } else { 
        mod = (*dp)[i] + ((ns[x] == ms[i + x - k]) ? 0 : 1);
      }

      (*new_dp)[i] = min(mod, min(add_n, add_m));
    }

    auto tmp = dp;
    dp = new_dp;
    new_dp = tmp;
  }

  if((*dp)[m - n + k] > k) {
    cout << "Muy distintas." << endl;
  } else {
    cout << (*dp)[m - n + k] << endl;
  }
}
