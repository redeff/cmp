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
  int n, a, b;
  cin >> n >> a >> b;

  int mx_x = 0;
  for(int i = 1; i < n; ++i) {
    mx_x = max(mx_x, min(a / i, b / (n - i)));
  }

  cout << mx_x << endl;

}

