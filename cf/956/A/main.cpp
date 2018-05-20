#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    int parent;
    int wei;
};

vector<UnionFind> create_union_find(int n) {
    vector<UnionFind> out(n);
    for(int i = 0; i < n; ++i) {
        out[i].parent = i;
        out[i].wei = 0;
    }
    return out;
}

int repr(int t, vector<UnionFind> &uf) {
    int init = t;
    while(t != uf[t].parent) {
        t = uf[t].parent;
    }
    int parent = t;
    t = init;
    while(t != uf[t].parent) {
        int next_chain = uf[t].parent;
        uf[t].parent = parent;
        t = next_chain;
    }
    return parent;
}

int join(int a, int b, vector<UnionFind> &uf) {
    int parent_a = repr(a, uf);
    int parent_b = repr(b, uf);
    if(parent_a == parent_b) return parent_a;

    if(uf[parent_a].wei == uf[parent_b].wei) {
        uf[parent_a].parent = parent_b;
        uf[parent_b].wei++;
    } else if(uf[parent_a].wei < uf[parent_b].wei) {
        uf[parent_a].parent = parent_b;
    } else {
        uf[parent_b].parent = parent_a;
    }

    int parent = repr(a, uf);
    return repr(a, uf);
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> board(n, vector<bool>(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            board[i][j] = c == '#';
        }
    }

    auto uf = create_union_find(n + m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(board[i][j]) {
                join(i, j + n, uf);
            }
        }
    }

    bool works = true;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(board[i][j] != (repr(i, uf) == repr(j + n, uf))) {
                works = false;
            }
        }
    }

    cout << (works ? "Yes" : "No") << endl;
}
