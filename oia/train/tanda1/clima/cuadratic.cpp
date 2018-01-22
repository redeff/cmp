#include <bits/stdc++.h>
using namespace std;

#define MAX 120
#define ifs cin
#define ofs cout
void dbg(vector<int> ns) {
  for(n : ns) cerr << n << " ";
  cerr << endl;
}

#define RAYA cerr << "=======================" << endl
// #define RAYA

#define ifs cin
#define ofs cout

int main() {
  /*
  ifstream ifs;
  ifs.open("clima.in");
  ofstream ofs;
  ofs.open("clima.out");
  */

  vector<int> ft(MAX + 8, 0);
  vector<int> as;
  vector<int> bs;

  int n;
  ifs >> n;

  for(int i = 0; i < n; ++i) {
    int p = 33333333; // Minima
    int q = -33333333; // Maxima
    int r;
    ifs >> r;
    for(int j = 0; j < r; ++j) {
      int pl, ql;
      ifs >> pl >> ql;
      p = min(p, pl);
      q = max(q, ql);
    }

    as.push_back(60 - p);
    bs.push_back(50 + q);
  }
  dbg(as);
  dbg(bs);
  RAYA;
  vector<int> lt(n, 0);
  vector<int> gt(n, 0);
  vector<int> et(n, 0);

  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      if(as[i] == as[j] && bs[i] == bs[j]) {
        et[i]++;
      } else if (as[i] <= as[j] && bs[i] <= bs[j]) {
        lt[i]++;
      } else if(as[i] >= as[j] && bs[i] >= bs[j]) {
        gt[i]++;
      }
    }
  }

  dbg(gt);
  dbg(lt);
  dbg(et);

  vector<int> maxs{0};
  for(int i = 1; i < n; ++i) {
    if(gt[maxs.back()] < gt[i]) {
      maxs = {i};
    } else if (gt[maxs.back()] == gt[i]) {
      maxs.push_back(i);
    }
  }

  for(int i : maxs) {
    ofs << (i + 1) << " " << (n - gt[i] - lt[i] - et[i]) << endl;
  }
}
