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

bool has7(int mm) {
  return mm % 10 == 7 || (mm >= 70 && mm <= 79);
}

int main(){
  int x;
  cin >> x;
  int h, m;
  cin >> h >> m;
  int minu = h * 60 + m;
  for(int i = 0;;++i) {
    int time = ((minu - x * i) % (60 * 24) + (60 * 24)) % (60 * 24);
    int mm = time % 60;
    int hh = time / 60;
    if(has7(hh) || has7(mm)) {
      cout << i << endl;
      return 0;
    }
  }
}

