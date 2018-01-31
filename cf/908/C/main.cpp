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
  int n, r;
  cin >> n >> r;

  vector<int> ns = get_vector<int>((ll) n);
  vector<double> his;

  forn(i, 0, n) {
    double best = r;

    forn(j, 0, i) if(abs(ns[j] - ns[i]) <= 2 * r) {
      best = max(best, his[j] + sqrt(4 * r * r - (ns[i] - ns[j]) * (ns[i] - ns[j])));
    }

    his.push_back(best);
  }

  cout.precision(12);
  for(auto h : his) cout << h << " ";
  cout << endl;
}

