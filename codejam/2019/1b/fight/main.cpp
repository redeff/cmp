#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

// const int N = 200000;
// pair<int, int> tree[2*N];


// st from: https://www.geeksforgeeks.org/segment-tree-efficient-implementation/
void build(int arr[], pair<int, int> tree[], int n) {
    for (int i=0; i<n; i++)
        tree[n+i] = {arr[i], i};

    for (int i = n - 1; i > 0; --i)
        tree[i] = max(tree[i<<1], tree[i<<1 | 1]);
}

pair<int, int> query(int l, int r, pair<int, int> tree[], int n) {
    pair<int, int> res = {-1, -1};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1)
            res = max(res, tree[l++]);
        if (r&1)
            res = max(res, tree[--r]);
    }
    return res;
}

ll choose2(ll d) {
    return d * (d-1ll) / 2ll;
}

ll rec(vector<int> &a, vector<pair<int, int>> &st_a, vector<int> &b, vector<pair<int, int>> &st_b, int l, int r) {
    if(r == l) return 0;
    int n = a.size();
    pair<int, int> mxa = query(l, r, &st_a[0], n);
    pair<int, int> mxb = query(l, r, &st_b[0], n);
    int total = 0;
    if(mxa.first > mxb.first) {
        total += choose2(r - l) - choose2(mxa.second - l) - choose2(r - mxa.second - 1);
        total += rec(a, st_a, b, st_b, l, mxa.second);
        total += rec(a, st_a, b, st_b, mxa.second+1, r);
    } else {
        total += rec(a, st_a, b, st_b, l, mxb.second);
        total += rec(a, st_a, b, st_b, mxb.second+1, r);
    }
    return total;
}

ll part(vector<int> a, vector<int> b) {
    int n = a.size();
    vector<pair<int, int>> st_a(4*n);
    build(&a[0], &st_a[0], n);
    vector<pair<int, int>> st_b(4*n);
    build(&b[0], &st_b[0], n);

    return rec(a, st_a, b, st_b, 0, n);
}

int main() {
    int t;
    cin >> t;
    for(int test = 0; test < t; ++test) {
        int n, k;
        cin >> n >> k;
        cerr << " " << k << endl;
        vector<int> as(n);
        for(int &i : as) cin >> i;
        vector<int> bs(n);
        for(int &i : bs) cin >> i;
        ll total = choose2(n);
        for(int &i : as) i -= k;
        total -= part(as, bs);
        for(int &i : as) i += 2*k;
        total -= part(bs, as);
        cout << total << endl;
    }
}
