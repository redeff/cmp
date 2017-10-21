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
  ll n, k;
  cin >> n >> k;
  vector<ll> a = get_vector<ll>(n);
  //Add a comment?

  if(k > 1){
    cout << "Yes" << endl;
  } else {
    ll b;
    cin >> b;
    bool is_sorted = true;
    forn(i, 1, n){
      is_sorted = is_sorted && (a[i - 1] == 0 ? b : a[i - 1]) < (a[i] == 0 ? b : a[i]);
    }
    if(is_sorted){
      cout << "No" << endl;
    } else {
      cout << "Yes" << endl;
    }
  }

}
