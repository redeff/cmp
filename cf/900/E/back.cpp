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

struct Cost {
  int ts; // How many ts fit in an interval
  int fills; // How many ?s we have to fill
  bool imposs; // It's impossible, infinite cost
  Cost(int ts, int fills, bool imposs): ts(ts), fills(fills), imposs(imposs) {}
  string to_s() {
    return "(" + to_string(ts) + ", " + to_string(fills) + ", " + to_string(imposs) + ")";
  }
  Cost(){}
};

bool operator<(Cost a, Cost b) {
  if(a.imposs) return false;
  if(b.imposs) return true;
  if(a.ts == b.ts) {
    return a.fills < b.fills;
  } else {
    return a.ts > b.ts; // The more it fills, the less it costs
  }
}

Cost operator+(Cost a, Cost b) {
  return Cost(a.ts + b.ts, a.fills + b.fills, a.imposs || b.imposs);
}

vector<Cost> cost_of_start; // Cost of filling a t starting at some index

vector<Cost> suffix_cost;

void calc_cost_of_start(string ns, int t) {
  int n = ns.size();
  vector<int> num_q{0};
  for(int i = 0; i < n; ++i) {
    num_q.push_back(num_q.back() + (ns[i] == '?'));
  }
  cost_of_start.resize(n - t);
  cout << cost_of_start.size() << endl;
  int last_prevents_even = -1;
  forn(i, 0, n) {
    if((i - t) % 2 == 0) {
      if(last_prevents_even < i - t) {
        cost_of_start[i - t] = Cost(1, num_q[i + 1] - num_q[i - t], false);
      } else if(i - t >= 0) {
        cost_of_start[i - t] = Cost(1, 0, true);
      }
    }
    if(i % 2 == 0 && ns[i] == 'b' || i % 2 == 1 && ns[i] == 'a') {
      last_prevents_even = i;
    }
  }
  cout << cost_of_start.size() << endl;

  int last_prevents_odd = -1;
  forn(i, 0, n) {
    if((i - t) % 2 == 1) {
      if(last_prevents_odd < i - t) {
        cost_of_start[i - t] = Cost(1, num_q[i] - num_q[i - t], false);
      } else {
        cost_of_start[i - t] = Cost(1, 0, true);
      }
    }
    if(i % 2 == 0 && ns[i] == 'a' || i % 2 == 1 && ns[i] == 'b') {
      last_prevents_odd = i;
    }
  }

  forn(i, 0, cost_of_start.size()) {
    cout << i << cost_of_start[i].to_s() << endl;
  }
}

Cost cost_of_suffix(int n, int t, int s) {
  if(n - s < t) return Cost(0, 0, true);
  if(n - s < t){
    suffix_cost[s] = Cost(0, 0, false);
    return Cost(0, 0, false);
  }

  Cost a = cost_of_suffix(n, t, s + 1);
  Cost b = cost_of_suffix(n, t, s + t) + cost_of_start[s];
  if(a < b) {
    suffix_cost[s] = a;
    return a;
  }
  suffix_cost[s] = b;
  return b;
}

int main(){
  int s;
  cin >> s;
  string ns;
  cin >> ns;
  int t;
  cin >> t;
  calc_cost_of_start(ns, t);
  suffix_cost = vector<Cost>(s, Cost(0, 0, true));
  cout << cost_of_suffix(s, t, 0).to_s() << endl;
}

