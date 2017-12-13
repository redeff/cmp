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
  int n;
  cin >> n;
  vector<int> xs;
  for(int i = 0; i < n; ++i) {
    xs.emplace_back();
    cin >> xs.back();
    int tmp;
    cin >> tmp;
  }
  sort(xs.begin(), xs.end());
  if(xs[1] > 0 || xs[xs.size() - 2] < 0) {
    cout << "Yes";
  } else {
    cout << "No";
  }


}

