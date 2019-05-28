#include <bits/stdc++.h>
using namespace std;

struct Conn {
    int to;
    int id;
};

int main() {
    int v, c, x, y;
    while(cin >> v >> c >> x >> y && v != 0) {
        vector<int> keys(v, -1);
        for(int i = 0; i < c; ++i) {
            int k;
            cin >> k;
            keys[k] = i;
        }

        vector<vector<Conn>> tree(v);
        for(int i = 0; i < v-1; ++i) {
            int a, b, l;
            cin >> a >> b >> l;
            tree[a].push_back(Conn {b, l});
            tree[b].push_back(Conn {a, l});
        }

        vector<bool> unlocked(c, false);
        vector<int> key_at(c, -1);
        vector<int> dad(v, -1);
        dad[x] = -1;
        vector<pair<int, int>> door_at;

        // for(int i : keys) cerr << i << " ";
        // cerr << "LA" << endl;
        bool seen_y = false;
        function<void (int, vector<bool>&)> dfs = [&](int node, vector<bool> &seen) {
            if(node == y) seen_y = true;
            if(seen[node]) return;
            seen[node] = true;
            if(keys[node] != -1) key_at[keys[node]] = node;
            for(Conn c : tree[node]) {
                if(c.id == -1 || unlocked[c.id]) {
                    if(!seen[c.to]) {
                        dad[c.to] = node;
                        // if(c.to == y) cerr << node << " - " << c.id << endl;
                    }
                    dfs(c.to, seen);
                }
                else if(c.id != -1) door_at.push_back({node, c.id});
            }
        };

        vector<int> all;

        for(int step = 0; step < 2*v + 100; ++step) {
            vector<bool> seen(v, false);
            dfs(x, seen);
            for(auto door : door_at) {
                int k = key_at[door.second];
                if(k != -1 && !unlocked[door.second]) {
                    // cerr << "YAA" << endl;
                    unlocked[door.second] = true;
                    vector<int> tokey;
                    while(k != -1) tokey.push_back(k), k = dad[k];
                    vector<int> todoor;

                    int d = door.first;
                    while(d != -1) todoor.push_back(d), d = dad[d];

                    reverse(tokey.begin(), tokey.end());
                    for(int i : tokey) all.push_back(i);
                    reverse(tokey.begin(), tokey.end());
                    for(int i : tokey) all.push_back(i);

                    reverse(todoor.begin(), todoor.end());
                    for(int i : todoor) all.push_back(i);
                    reverse(todoor.begin(), todoor.end());
                    for(int i : todoor) all.push_back(i);
                }
            }
            // door_at.clear();
        }

        // if(unlocked.size() > 0) cerr << dad[y] << " y" << endl;
        if(!seen_y) {
            cout << "Impossible" << endl;
        } else {
            vector<int> toexit;
            while(y != -1) toexit.push_back(y), y = dad[y];
            reverse(toexit.begin(), toexit.end());
            for(int i : toexit) all.push_back(i);

            all.erase(unique(all.begin(), all.end()), all.end());

            cout << all.size()-1 << ":";
            for(int i : all) cout << " " << i;
            cout << endl;
        }
    }
}
