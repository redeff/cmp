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

int ch(int n) {
  vector<int> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67}; 

  for(int c : {49, 25, 9, 4, 4, 4, 4, 4, 4}) {
    if(n % c == 0) n /= c;
  }

  int out = 0;
  forn(i, 0, primes.size()) {
    if(n % primes[i] == 0) {
      out ^= 1 << i;
    }
  }

  return out;
}

int main(){
  ll total = 1;

  ll n;
  cin >> n;
  vector<int> nums;
  forn(i, 0, n) {
    int l;
    cin >> l;
    nums.push_back(ch(l));
  }

  unordered_set<int> poss {0};


  forn(i, 0, n) {
    if(poss.count(nums[i]) == 1) {
      total *= 2;
      total = total % MOD;
    } else {
      unordered_set<int> n_poss;
      for(int p : poss) {
        n_poss.insert(p);
        n_poss.insert(p ^ nums[i]);
      }

      swap(poss, n_poss);
    }
  }

  cout << total - 1;
}
