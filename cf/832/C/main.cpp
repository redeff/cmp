#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7
double LIMIT = 1000000.0 //10^6

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

double takes(double rs, double rp, double ls, double lp, double s){
  if(rp < lp) return -1; 
  double takes_alone = lp / ls + (LIMIT - rp) / rs;
  if(takes_alone * s < LIMIT) return -1;

int main(){
  vector<ll> r; //Yhose who face right
  vector<ll> l; //Those who face left
  ll s; //Bomb speed

}
