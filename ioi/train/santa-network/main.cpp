#include <bits/stdc++.h>
using namespace std;

struct Conn {
    int to;
    double wei;
};

struct BiConn {
    int a;
    int b;
    double wei;
};

double prob(double k, double n) {
    double one_side = (k / n) * ((k - 1) / (n - 1)) * ((k - 2) / (n - 2));
    k = n - k;
    double other_side = (k / n) * ((k - 1) / (n - 1)) * ((k - 2) / (n - 2));
    return 2 * (1 - one_side - other_side);
}

int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);

    int n;
    cin >> n;
    
    vector<vector<Conn>> tree(n);
    vector<BiConn> conns(0);
    for(int i = 0; i < n-1; ++i) {
        int a, b;
        int wei;
        cin >> a >> b >> wei;
        a--; b--;
        tree[a].push_back({b, (double)wei});
        tree[b].push_back({a, (double)wei});
        conns.push_back({a, b,(double)wei});
    }

    vector<int> subtree(n, -1);
    function<void(int)> calc = [&](int node) {
        subtree[node] = 0;
        int total = 0;
        for(Conn c : tree[node]) {
            if(subtree[c.to] == -1) calc(c.to);
            total += subtree[c.to];
        }
        subtree[node] = total + 1;
    };


    calc(0);

    double expected = 0;
    for(int i = 0; i < n-1; ++i) {
        expected += conns[i].wei * prob((double) min(subtree[conns[i].a], subtree[conns[i].b]), (double) n);
    }

    int q;
    cin >> q;
    cout << setprecision(10);
    cout << fixed;
    for(int i = 0; i < q; ++i) {
        int k;
        int wei;
        cin >> k >> wei;
        --k;
        expected += ((double)wei - conns[k].wei) * prob((double) min(subtree[conns[k].a], subtree[conns[k].b]), (double) n);
        conns[k].wei = (double)wei;
        cout << expected << endl;
    }
    // cerr << "Hello" << endl;
}
