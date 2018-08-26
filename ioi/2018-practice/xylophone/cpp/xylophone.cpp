#include "xylophone.h"
#include <bits/stdc++.h>
using namespace std;

#define ALL(x) x.begin(), x.end()

unordered_map<int, int> memo;
int ask_memo(int a, int b) {
    int hash = a + b;
    if(memo.count(hash) == 0) {
        int ans = ask(a, b);
        memo[hash] = ans;
        return ans;
    } else {
        return memo[hash];
    }
}

void detect_pitch(int n) {
    vector<int> diffs(n-1);
    diffs[0] = ask_memo(0, 1);

    int dir = 1;

    for(int i = 1; i < n-1; ++i) {
        if(ask_memo(i-1, i) + ask_memo(i, i+1) != ask_memo(i-1, i+1)) dir *= -1;
        diffs[i] = ask_memo(i, i+1) * dir;
    }

    vector<int> ns(n);
    ns[0] = 0;
    for(int i = 1; i < n; ++i) ns[i] = ns[i-1] + diffs[i-1];
    if(min_element(ALL(ns)) > max_element(ALL(ns))) for(int &i : ns) i *= -1;
    int mn = *min_element(ALL(ns));
    for(int &i : ns) i -= mn;
    for(int i = 0; i < n; ++i) answer(i, ns[i]);
}
