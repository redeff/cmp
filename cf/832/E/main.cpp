//TODO
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
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

int inv(int a){
  a = a % 5;
  if(a == 1) return 1;
  if(a == 2) return 3;
  if(a == 3) return 2;
  if(a == 4) return 4;
  return 0;
}

string prime(vector<int> rems){
  string out;
  if(rems[0] == 1){
    for(int i : rems){
      out.push_back('0' + i);
    }
  } else {
    ll l = inv(rems[1]);
    for(int i : rems){
      out.push_back(
int main(){

}
