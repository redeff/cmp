#include <bits/stdc++.h>
using namespace std;

#define MAX 120

int lsb(int x) {
  return x & -x;
}

// Toma la suma de los valores del
// array en [0, index)
int get_ft(int index, vector<int> &ft) {
  int v = 0;
  for(int x = index; x > 0; x -= lsb(x)) {
    v += ft[x];
  }
  return v;
}

// Aumenta en 1 el valor en indice $index
void set_ft(int index, vector<int> &ft) {
  index += 1;
  for(int x = index; x < ft.size(); x += lsb(x)) {
    ft[x] += 1;
  }
}

void dbg(vector<int> ns) {
  //for(n : ns) cerr << n << " ";
  //cerr << endl;
}

// #define RAYA cerr << "=======================" << endl
#define RAYA

/*
#define ifs cin
#define ofs cout
*/
int main() {
  ifstream ifs;
  ifs.open("clima.in");
  ofstream ofs;
  ofs.open("clima.out");

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

  vector<int> iot(n);
  iota(iot.begin(), iot.end(), 0);

  vector<int> lt(n);
  vector<int> gt(n);

  sort(iot.begin(), iot.end(), [&](int x, int y) {
    if(as[x] != as[y]) return as[x] < as[y];
    if(bs[x] != bs[y]) return bs[x] < bs[y];
    return x < y; 
  });

  dbg(iot);

  for(int i = 0; i < n; ++i) {
    set_ft(bs[iot[i]], ft);
    gt[iot[i]] = get_ft(bs[iot[i]] + 1, ft);
  }

  ft = vector<int>(128, 0);

  sort(iot.begin(), iot.end(), [&](int x, int y) {
    if(as[x] != as[y]) return as[x] > as[y];
    if(bs[x] != bs[y]) return bs[x] > bs[y];
    return x > y; 
  });

  dbg(iot);
  RAYA;

  for(int i = 0; i < n; ++i) {
    set_ft(MAX - bs[iot[i]], ft);
    lt[iot[i]] = get_ft(MAX - bs[iot[i]] + 1, ft);
  }

  vector<int> et = vector<int>(n, 1);

  for(int i = 1; i < n; ++i) {
    if(as[iot[i]] == as[iot[i - 1]] && bs[iot[i]] == bs[iot[i - 1]]) {
      et[iot[i]] = et[iot[i - 1]] + 1;
      gt[iot[i]] = gt[iot[i - 1]];
    }
  }

  for(int i = n - 2; i >= 0; --i) {
    if(as[iot[i]] == as[iot[i + 1]] && bs[iot[i]] == bs[iot[i + 1]]) {
      et[iot[i]] = et[iot[i + 1]];
      lt[iot[i]] = lt[iot[i + 1]];
    }
  }

  dbg(gt);
  dbg(lt);
  dbg(et);
  RAYA;

  vector<int> maxs{0};
  for(int i = 1; i < n; ++i) {
    if(gt[maxs.back()] - et[maxs.back()] < gt[i] - et[i]) {
      maxs = {i};
    } else if (gt[maxs.back()] - et[maxs.back()] == gt[i] - et[i]) {
      maxs.push_back(i);
    }
  }

  for(int i : maxs) {
    ofs << (i + 1) << " " << (n - gt[i] - lt[i] + et[i]) << endl;
  }
}
