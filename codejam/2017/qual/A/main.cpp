#include <bits/stdc++.h>
using namespace std;
void testcase() {
    string s;
    int k;
    cin >> s >> k;
    int n = s.size();

    vector<bool> ns(n);
    for(int i = 0; i < n; ++i) ns[i] = s[i] == '+';
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

    for(int i = n - k + 1; i < n; ++i) {
        if(flips[i]) works = false;
    } 

    for(int i = 0; i < n; ++i) {
        if(flips[i]) total++;
    }

    if(works) cout << total << endl;
    else cout << "IMPOSSIBLE" << endl;
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cout << "Case #" << i + 1 << ": ";
        testcase();
    }
}
