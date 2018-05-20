#include <bits/stdc++.h>
const int INF = 333333333;
using namespace std;

int rec(vector<bool> ns, int k) {
    // for(bool b : ns) cerr << b;
    // cerr << endl;
    if(k > ns.size()) {
        bool works = true;
        for(bool b : ns) if(!b) works = false;
        return works ? 0 : INF;
    } else {
        int p1 = ns.back() ? 0 : 1;
        for(int i = ns.size() - k; i < ns.size(); ++i) {
            ns[i] = ns[i] == ns.back();
        }
        ns.pop_back();
        return p1 + rec(ns, k);
    }
}

void testcase() {
    string s;
    int k;
    cin >> s >> k;
    int n = s.size();

    vector<bool> ns(n);
    for(int i = 0; i < n; ++i) ns[i] = s[i] == '+';

    int res = rec(ns, k);
    if(res >= INF) cout << "IMPOSSIBLE" << endl;
    else cout << res << endl;

    /*
    vector<bool> flips(n);

    flips[0] = !ns[0];
    for(int i = 1; i < k; ++i) {
        flips[i] = ns[i] != ns[i - 1]; 
    }

    for(int i = k; i < n; ++i) {
        flips[i] = ns[i] != ns[i - 1] != flips[i - k];
    }

    for(int i = 0; i < n; ++i) cerr << flips[i];
    cerr << endl;

    bool works = true;
    int total = 0;

    for(int i = n - k; i < n; ++i) {
        if(flips[i]) works = false;
    } 

    for(int i = 0; i < n; ++i) {
        if(flips[i]) total++;
    }

    if(works) cout << total << endl;
    else cout << "IMPOSSIBLE" << endl;
    */
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cout << "Case #" << i + 1 << ": ";
        testcase();
    }
}
