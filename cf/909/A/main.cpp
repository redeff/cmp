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
  string a, b;
  cin >> a >> b;
  vector<string> poss;
  string curr = "";
  for(int i = 0; i < a.size(); ++i) {
    curr.push_back(a[i]);
    curr.push_back(b[0]);
    poss.push_back(curr);
    curr.pop_back();
  }

  sort(poss.begin(), poss.end());
  cout << poss[0] << endl;

}

