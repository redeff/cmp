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
  int h1, a1, c1;
  int h2, a2;

  cin >> h1 >> a1 >> c1 >> h2 >> a2;

  int h1_c = h1;
  int h2_c = h2;

  int index = 0;
  string things;
  while(true) {
    index++;
    if(h2_c <= a1) {
      things.append("STRIKE\n");
      break;
    }

    if(a2 >= h1_c) {
      h1_c += c1;
      things.append("HEAL\n");
    } else {
      h2_c -= a1;
      things.append("STRIKE\n");
    }

    h1_c -= a2;
  }

  cout << index << endl;
  cout << things;


}

