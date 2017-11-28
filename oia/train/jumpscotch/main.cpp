#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> ns;
int n;
int d;
 
vector<int> minima;
list<int> curr_best;

int head;
int tail;

void move_head() {
  head--;
  minima[head] = ns[head] + minima[curr_best.back()];

  while(minima[curr_best.front()] >= minima[head]) {
    curr_best.pop_front();
  }

  curr_best.push_front(head);
}

void move_tail() {
  tail--;
  while(tail < curr_best.back()) {
    curr_best.pop_back();
  }
}

int main() {
  cin >> n >> d;
  for(int i = 0; i < n; ++i) {
    ns.emplace_back();
    cin >> ns.back();
  }

  minima.resize(n);

  head = n - 1;
  tail = n - 1;

  curr_best.push_back(n - 1);
  minima[n - 1] = ns[n - 1];

  while(head > 0) {
    if(tail - head >= d) {
      move_tail();
    }
    move_head();
  }

  cout << minima[0] << endl;
}
