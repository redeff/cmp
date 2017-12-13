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

bool check_string(string s, vector<string> ns, int k) {
  bool works = true;
  for(auto n : ns) {
    vector<int> doesnt_work;
    forn(i, 0, k) {
      if(n[i] != s[i]) doesnt_work.push_back(i);
    }
    if(doesnt_work.size() > 2 || doesnt_work.size() == 1){
      works = false; break;
    }
    if(doesnt_work.size() == 0) continue;
    if(n[doesnt_work[0]] != s[doesnt_work[1]] || n[doesnt_work[1]] != s[doesnt_work[0]]) {
      works = false;
      break;
    }

  }

  return works;
}

int main(){
  int n, k;
  cin >> n >> k;
  vector<string> ns = get_vector<string>(n);

  int diff = 0;
  forn(i, 1, n) {
    if(ns[i - 1] != ns[i]) {
      diff = i;
    }
  }

  if(diff == 0) {
    cout << ns[0];
  } else {
    unordered_map<int> diff_index;
    string candidate
    forn(i, 0, k) {
      if(ns[diff][i] != ns[diff - 1][i]) {
        unordered_map.push_back(i);
        candidate.push_back('#');
      } else {
        candidate.push_back(ns[diff][i]);
      }
    }

    if(diff_index.size() > 4) {
      cout << "-1" << endl;
    } else {
      unordered_map<int> has_to_have;
      string must_be;
      forn(i, 0, n) {
        unordered_map<int> extras;
        for(j, 0, k) {
          if(candidate[j] != '#' && ns[i][j] != candidate[j]) {
            extras.push_back(j);
          }
        }

        if(extras.size() > 2) {
          cout << "-1" << endl;
          return 0;
        }
        
        if(extras.size() == 2) {
          // It must be conditate || ns[i]
          for(j, 0, k) {
            must_be.push_back(candidate[j] == '#' ? ns[i][j] : candidate[j]);
          }

          goto must_be_s;
        }
      }


must_be_s:
      ;
      if(check_string(must_be, ns, k)) {
        cout << must_be;
      } else {
        cout << "-1";
      }
    }





}

