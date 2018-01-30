#include <bits/stdc++.h>
const int INF = 333333333;

using namespace std;
string wd;
int n;

vector<vector<int>> prefix;
vector<vector<int>> suffix;
vector<vector<int>> dp; // s and e reversed

int rec(int s, int e) { // nivelacion(word[s][e]) - len(word[s;e])
    if(e == s - 1) return 0;
    if(dp[e][s] != -1) {
        return dp[e][s];
    }
    int ret;
    if(e == s) {
        ret = -1;
    } else if(wd[s] == wd[e]) {
        ret = rec(s + 1, e - 1) - 2;
    } else {
        ret = min(prefix[s][e - s], suffix[e][e - s]);
    }

    if(prefix[s].size() > e-s+1)
        prefix[s][e-s+1] = min(prefix[s][e-s], ret);
    if(suffix[e].size() > e-s+1)
        suffix[e][e-s+1] = min(suffix[e][e-s], ret);
    dp[e][s] = ret;

    return ret;
}

int nivelacion(string word){
    wd = word;
    n = word.size();
    prefix = vector<vector<int>>(n);
    suffix = vector<vector<int>>(n);
    dp = vector<vector<int>>(n);

    for(int s = 0; s < n; ++s) {
        prefix[s] = vector<int>(n - s + 1, INF);
        prefix[s][0] = 0;
    }

    for(int e = 0; e < n; ++e) {
        suffix[e] = vector<int>(e + 1, INF);
        suffix[e][0] = 0;
    }

    for(int e = 0; e < n; ++e) {
        dp[e] = vector<int>(e + 1, -1); 
    }

    for(int len = 1; len < n; ++len) {
        for(int s = 0; s + len <= n; ++s) {
            rec(s, s + len - 1);
        }
    }

    // cout << n + rec(0, n - 1) << endl;
    return rec(0, n - 1) + n;
}
