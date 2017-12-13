#include <bits/stdc++.h>
using namespace std;

#define forn(i, a, b) for(int i = a; i < b; ++i)

struct Cost {
  int ts; // the number of strings t the 
  int qs; // the number of question marks that have to be filled to achieve it
  bool poss; // is it even possible
  Cost(int ts, int qs, bool poss): ts(ts), qs(qs), poss(poss) {}
  Cost(){}
};

bool operator<(Cost a, Cost b) {
  if(!a.poss && !b.poss) {
    return false;
  } else if (!b.poss) {
    return true;
  } else if (!a.poss) {
    return false;
  } else {
    if(a.ts == b.ts) return a.qs < b.qs;
    else return a.ts > b.ts;
  }
}

Cost operator+(Cost a, Cost b) {
  return Cost(a.ts + b.ts, a.qs + b.qs, a.poss && b.poss);
}

Cost min(Cost a, Cost b) {
  if(a < b) return a;
  else return b;
}

Cost impossible(){
  return Cost(0, 0, false);
}

Cost possible(int ts, int qs) {
  return Cost(ts, qs, true);
}

vector<int> calc_qs_partial_sum(string s) {
  vector<int> out{0};
  for(char c : s) {
    out.push_back(out.back() + (c == '?'));
  }
  return out;
}
vector<Cost> calc_cost_of_start_with_parity(string s, int n, int t, vector<int> qs_partial_sum, bool parity) {
  vector<Cost> out(n, impossible());
  string should_be;
  if(parity) {
    should_be = "ab";
  } else {
    should_be = "ba";
  }

  vector<bool> is_what_should(n);
  forn(i, 0, n) {
    is_what_should[i] = s[i] == should_be[i % 2] || s[i] == '?';
  }
  
  vector<bool> can_be(n);
  int last_that_breaks = -1;
  forn(i, 0, n) {
    if(!is_what_should[i]) last_that_breaks = i;
    if(last_that_breaks < i - (t - 1)) {
      if(((i - t + 1) % 2 == 0) == parity) {
        out[i - t + 1] = possible(1, qs_partial_sum[i + 1] - qs_partial_sum[i - t + 1]);
      } else {
        out[i - t + 1] = impossible();
      }
    }
  }

  return out;
}

vector<Cost> calc_cost_of_start(string s, int n, int t) {
  auto qs_partial_sum = calc_qs_partial_sum(s);
  auto even = calc_cost_of_start_with_parity(s, n, t, qs_partial_sum, true);
  auto odd = calc_cost_of_start_with_parity(s, n, t, qs_partial_sum, false);
  vector<Cost> out(n);
  forn(i, 0, n) {
    out[i] = min(even[i], odd[i]);
  }

  return out;
}


unordered_map<int, Cost> dp;
Cost calc_cost_of_suffix_rec(vector<Cost> const& cost_of_start, int n, int t, int suffix) {
  if(suffix > n) return impossible();
  if(suffix == n) return possible(0, 0);

  else if(dp.count(suffix) > 0) return dp[suffix];
  else {
    Cost ret;
    ret = min(
        calc_cost_of_suffix_rec(cost_of_start, n, t, suffix + 1), 
        calc_cost_of_suffix_rec(cost_of_start, n, t, suffix + t) + cost_of_start[suffix]
    );
    dp[suffix] = ret;
    return ret;
  }
}


int main(){
  int n;
  cin >> n;
  string s;
  cin >> s;
  int t;
  cin >> t;
  auto cost_of_start = calc_cost_of_start(s, n, t);
  cout << calc_cost_of_suffix_rec(cost_of_start, n, t, 0).qs << endl;

}

