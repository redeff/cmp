#include <bits/stdc++.h>
using namespace std;
void testcase() {
    string s;
    int k;
    cin >> s >> k;
    int n = s.size();

    vector<bool> ns(n);
    for(int i = 0; i < n; ++i) ns[i] = s[i] == '+';

    bool works = true;
    int total = 0;

    for(int i = 0; i < n; ++i) {
        if(!ns[i]) {
            if(i + k > n) {
                works = false;
                break;
            } else for(int j = i; j < i + k; ++j) {
                ns[j] = !ns[j];
            }
            total++;
        }
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
