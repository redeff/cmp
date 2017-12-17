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

int check_range(int a, int b, int t) {
  if(t < a) return - 1;
  if(t > b) return 1;
  return 0;
}

int main(){
  int n;
  cin >> n;
  auto ns = get_vector<int>((ll)n);

  if(n == 1) {
    cout << ns[0] << endl;
  } else {
    int a, b; // Second biggest, and biggest
    vector<int> killers;
    vector<int> records;
    records.push_back(0);
    if(ns[0] > ns[1]) {
      killers.push_back(0);
      b = 0;
      a = 1;
    } else {
      records.push_back(1);
      b = 1;
      a = 0;
    }

    forn(i, 2, n) {
      switch(check_range(ns[a], ns[b], ns[i])) {
        case -1:
          break;
        case 0:
          killers.push_back(b);
          a = i;
          break;
        case 1:
          records.push_back(i);
          a = b;
          b = i;
          break;
      }
    }

    vector<int> values(n, 0);
    for(auto i : killers) values[i]++;
    for(auto i : records) values[i]--;

    vector<int> indices(n);
    forn(i, 0, n) indices[i] = i;
    auto it = max_element(indices.begin(), indices.end(), [&](int a, int b) {
        if(values[a] == values[b]) return ns[a] > ns[b];
        return values[a] < values[b];
    });

    cout << ns[*it] << endl;
  }
}

