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
  ll n, m;
  cin >> n >> m;
  vector<int> ns = get_vector<int>(n);
  vector<int> ms = get_vector<int>(m);

  int ln = *min_element(ns.begin(), ns.end());
  int lm = *min_element(ms.begin(), ms.end());

  vector<int> large(100);

  sort(ns.begin(), ns.end());
  sort(ms.begin(), ms.end());

  auto it = set_intersection(ns.begin(), ns.end(), ms.begin(), ms.end(), large.begin());


  if(it != large.begin()){
    cout << *large.begin() << endl;
  } else if(ln == lm){
    cout << ln << endl;
  } else if (ln < lm) {
    cout << ln << lm << endl;
  } else {
    cout << lm << ln << endl;
  }
}
