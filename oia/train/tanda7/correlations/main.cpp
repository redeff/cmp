#include <bits/stdc++.h>
using namespace std;

bool testcase() {
    int n, m;
    if(!(cin >> n)) return false;
    cin >> m;

    vector<vector<int>> dag(n);
    vector<int> needed(n, 0);
    vector<bool> passed(n, false);

    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        dag[a].push_back(b);
        needed[b]++;
    }

    int total = 0;

    function<void(int)> update = [&](int k) {
        if(needed[k] == 0 && passed[k]) {
            total++;
            for(int c : dag[k]) {
                needed[c]--;
                update(c);
            }
        }        
    };

    for(int i = 0; i < n; ++i) {
        int s;
        cin >> s;
        s--;
    
        passed[s] = true;
        update(s);

        cout << total << endl;
    }

    return true;
}

int main() {
    while(testcase());

    return 0;
}
