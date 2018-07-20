#include <bits/stdc++.h>
using namespace std;

struct BiConn {
    int a;
    int b;
};

struct Conn {
    int to;
    int id;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        int n, c;
        cin >> n >> c;
        if(n == 0) break;
        vector<vector<int>> dual(n);
        vector<vector<int>> conf(c);
        for(int i = 0; i < c; ++i) {
            int k;
            cin >> k;
            conf[i] = vector<int>(k);
            for(int j = 0; j < k; ++j) cin >> conf[i][j];

            for(int j = 0; j < k; ++j) {
                dual[conf[i][j]].push_back(conf[i][(j+1)%k]);
                // dual[conf[i][(j+1)%k]].push_back(conf[i][j]);
            }
        }

        int num_odd = 0;
        for(auto &v : conf) {
            int deg = 0;
            for(int city : v) {
                if(dual[city].size() != 1) deg++;
            }
            num_odd += deg % 2;
        }

        int chosen;
        
        if(num_odd == 0) {
            chosen = 0;
        } else if(num_odd == 2) {
            chosen = n + 1;
            for(auto &v : conf) {
                int deg = 0;
                for(int city : v) {
                    if(dual[city].size() != 1) deg++;
                }
                if(deg % 2 == 1) {
                    for(int city : v) {
                        chosen = min(chosen, city);
                    }
                }
            }
        } else {
            chosen = -1;
        }

        vector<bool> seen(n, false);
        function<void(int)> see = [&](int node) {
            if(seen[node]) return;
            seen[node] = true;
            for(int ch : dual[node]) {
                see(ch);
            }
        };

        see(0);

        for(int i = 0; i < n; ++i) if(seen[i] == false) chosen = -1;

        cout << chosen << endl;
    }
}
