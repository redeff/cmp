#include <bits/stdc++.h>
using namespace std;

#define DEPTH(n) tree[n].depth
#define ANS(n, k) tree[n].ans[k]

// Floor of log2(n)
int flg(int n) {
    return 8 * (sizeof (int)) - __builtin_clz(n) - 1;
}

struct Node {
    vector<int> ans;
    int depth;
    int index;
};

vector<Node> build(vector<vector<int>> ch) {
    int n = ch.size();
    int ln = flg(n) + 1;
    vector<Node> tree(n);
    for(int i = 0; i < n; ++i) {
        tree[i].ans = vector<int>(ln);
        tree[i].depth = -1;
    }

    ANS(0, 0) = 0;
    DEPTH(0) = 0;
    for(int i = 0; i < n; ++i) {
        for(int c : ch[i]) {
            ANS(c, 0) = i;
        }
    }

    function<void(int)> depth = [&](int n) -> void {
        if(DEPTH(n) != -1) return;
        else {
            depth(ANS(n, 0));
            DEPTH(n) = DEPTH(ANS(n, 0)) + 1;
        }
    };

    for(int i = 0; i < n; ++i) {
        depth(i);
        for(int k = 1; k < ln; ++k) {
            ANS(i, k) = ANS(ANS(i, k - 1), k - 1);
        }
    }

    return tree;
}

int lca(vector<Node> &tree, int a, int b) {
    if(DEPTH(a) > DEPTH(b)) {
        auto c = a;
        a = b;
        b = c;
    }
    while(DEPTH(a) != DEPTH(b)) {
        b = ANS(b, flg(DEPTH(b) - DEPTH(a)));
    }

    if(a == b) return a;
    else {
        for(int s = flg(tree.size()); s >= 0; --s) {
            if(ANS(a, s) != ANS(b, s)) {
                a = ANS(a, s);
                b = ANS(b, s);
            }
        }
    }

    return ANS(a, 0);
}

int main() {
    int t;
    cin >> t;
    for(int lala = 0; lala < t; ++lala) {
        cout << "Case " << lala + 1 << ":" << endl;
        int n;
        cin >> n;
        vector<vector<int>> ch(n);
        for(int i = 0; i < n; ++i) {
            int m;
            cin >> m;
            for(int j = 0; j < m; ++j) {
                int k;
                cin >> k;
                k--;
                ch[i].push_back(k);
            }
        }

        auto tree = build(ch);

        int q;
        cin >> q;
        for(int i = 0; i < q; ++i) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            cout << lca(tree, a, b) + 1 << endl;
        }
    }
}
