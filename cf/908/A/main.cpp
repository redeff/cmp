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
  string s;
  cin >> s;

  string poss = "aeiou13579";

  int total = 0;
  for(char c : s) {
    for(char p : poss) {
      if(c == p) total ++;
    }
  }

  cout << total << endl;


}

