#include <bits/stdc++.h>
using namespace std;


const int INF = 33333333;
// Ancho, Alto, x, y
vector<vector<vector<vector<int>>>> dp;

vector<pair<int, int>> by_x;
vector<pair<int, int>> by_y;

// #define S << " " <<
#define cin ifs
#define cout ofs
int main() {
  ifstream ifs("placas.in");
  ofstream ofs("placas.out");

  int k, n;

  cin >> k >> n;

  for(int i = 0; i < n; ++i) {
    by_x.emplace_back();
    cin >> by_x.back().first;
    cin >> by_x.back().second;
  }

  by_y = by_x;

  sort(by_x.begin(), by_x.end(), [](pair<int, int> a, pair<int, int> b) { return a.first < b.first; });
  sort(by_y.begin(), by_y.end(), [](pair<int, int> a, pair<int, int> b) { return a.second<b.second; });

  dp.emplace_back();
  for(int w = 1; w <= n; ++w) {
    dp.emplace_back();
    dp.back().emplace_back();
    for(int h = 1; h <= n; ++h) {
      dp.back().emplace_back();
      for(int x = 0; x < n - w + 1; ++x) {
        dp.back().back().emplace_back();
        for(int y = 0; y < n - h + 1; ++y) {
          dp.back().back().back().emplace_back();

          if(by_x[x].second < by_y[y].second || by_x[x].second > by_y[y + h - 1].second) {
            dp[w][h][x][y] = (w == 1) ? 0 : dp[w - 1][h][x + 1][y];
            // cerr << "1F ";
          } else if(by_x[x + w - 1].second < by_y[y].second || by_x[x + w - 1].second > by_y[y + h - 1].second) {
            dp[w][h][x][y] = (w == 1) ? 0 : dp[w - 1][h][x][y];
            // cerr << "2F ";
          } else if(by_y[y].first < by_x[x].first || by_y[y].first > by_x[x + w - 1].first) {
            dp[w][h][x][y] = (h == 1) ? 0 : dp[w][h - 1][x][y + 1];
            // cerr << "3F ";
          } else if(by_y[y + h - 1].first < by_x[x].first || by_y[y + h - 1].first > by_x[x + w - 1].first) {
            dp[w][h][x][y] = (h == 1) ? 0 : dp[w][h - 1][x][y];
            // cerr << "4F ";
          } else {
            // int best = -INF;

            int best = 0;
            best += 2 * (by_x[x + w - 1].first - by_x[x].first);
            best += 2 * (by_y[y + h - 1].second - by_y[y].second);
            best += 8 * k;
            // cout << best << " : ";

            for(int d = 1; d < w; ++d) {
              int a = dp[d][h][x][y];
              int b = dp[w - d][h][x + d][y];


              best = min(best, a + b);
                // cerr << "   " << a << " = " << d S h S x S y << endl;
                // cerr << "   " << b << " = " << w - d S h S x + d S y << endl;
              // cout << "    " << d << " " << h << " " << x << " " << y << << " + "
                //<< w - d << " " << h << " " << x + d << " " << y << " => " << nw << endl;
            }

            for(int d = 1; d < h; ++d) {
              best = min(best, dp[w][d][x][y] + dp[w][h - d][x][y + d]);
            }

            dp[w][h][x][y] = best;
          }
          // cout << w << " " << h << " " << x << " " << y << " => " << dp[w][h][x][y] << endl;
        }
      }
    }
  }

  cout << dp[n][n][0][0] << endl;
}
