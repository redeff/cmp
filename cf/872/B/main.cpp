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
  vector<ll> v = get_vector<ll>(n);

  if (k == 1) {

    cout << *min_element(v.begin(), v.end());

  } else if (k == 2) {

    cout << max(max(*v.begin(), *min_element(v.begin() + 1, v.end())), max(*v.rbegin(), *min_element(v.begin(), v.end() - 1)));

  } else {

    cout << *max_element(v.begin(), v.end());

  }

  cout << endl;

}
