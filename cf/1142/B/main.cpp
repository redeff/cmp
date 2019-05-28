#include <bits/stdc++.h>
using namespace std;

vector<int> comp(vector<int> &a, vector<int> &b) {
    assert(a.size() == b.size());
    int n = (int) a.size();
    vector<int> c(n);
    for(int i = 0; i < n; ++i) c[i] = a[b[i]];

    return c;
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> ns(n);
    for(int &i : ns) cin >> i, --i;

    vector<int> ms(m);
    for(int &i : ms) cin >> i, --i;

    vector<int> inv(n);
    for(int i = 0; i < n; ++i) inv[ns[i]] = i;
    for(int &i : ms) i = inv[i];


    vector<int> last(n, -1);
    vector<int> dp(m+1, 0);
    for(int i = 0; i < m; ++i) {
        dp[i+1] = 1+last[(ms[i] + n - 1) % n];
        last[ms[i]] = i;
    }

    vector<int> pos(m + 1);
    iota(pos.begin(), pos.end(), 0);

    n--;
    while(n != 0) {
        if(n % 2) pos = comp(pos, dp);
        dp = comp(dp, dp);
        n /= 2;
    }

    for(int i = 1; i <= m+1; ++i) {
        pos[i] = max(pos[i], pos[i-1]);
    }

    for(int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        // l--; r--;
        cout << (pos[r] >= l);
    }
    cout << endl;
}
