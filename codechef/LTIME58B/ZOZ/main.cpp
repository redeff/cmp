#include <bits/stdc++.h>
using namespace std;

#define ALL(lalala) lalala.begin(), lalala.end()

void doit() {
    int n, k;
    cin >> n >> k;
    vector<int> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i];

    int sum = accumulate(ALL(ns), 0);

    int total = 0;
    for(auto x : ns) if(2 * x + k > sum) total++;
    cout << total << endl;
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) doit();
}
