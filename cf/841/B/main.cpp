#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(int i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7

template <typename T>
void get_vector(ll size){
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
  char a, b;
  cin >> a;
  while(cin >> b){
    if(b == ' ' || b == '\n'){
      if(a == '1' || a == '3' || a == '5' || a == '7' || a == '9'){
        cout << "First" << endl;
        return 0;
      }
    }
    a = b;
  }

  if(b == '1' || b == '3' || b == '5' || b == '7' || b == '9'){
    cout << "First" << endl;
    return 0;
  }
 
  cout << "Second" << endl;

}
