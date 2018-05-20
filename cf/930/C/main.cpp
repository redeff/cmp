#include <bits/stdc++.h>
using namespace std;

/*
void add_ft(int val, int index, vector<int> &ft) {
    for(int i = index; i < ft.size(); i += i & -i) {
        ft[i] += val;
    }
}

int get_ft(int index, vector<int> &ft) {
    int total = 0;
    for(int i = index; i; i -= i & -i) {
        total += vals[i];
    }
    return total;
}
*/

int main() {
    int n, m;
    cin >> n >> m;

    /*
    vector<int> ft(m, 0);

    for(int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        add_ft();
    }
    */
    vector<int> sts(m + 1, 0);
    for(int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        sts[r + 1]--;
        sts[l]++;
    }

    vector<int> ans(m);
    ans[0] = sts[0];
    for(int i = 1; i < m; ++i) {
        ans[i] = ans[i - 1] + sts[i];
    }

    for(int i = 0; i < m; ++i) {
        // cout << ans[i] << " ";
    }
    // cout << endl;

    vector<int> l_rs(m);
    {
        vector<int> pa(m);
        vector<int> ma(m + 1);
        int l = 0;
        for(int i = 0; i < m; ++i) {
            int lo = 0;
            int hi = l + 1;
            while(lo < hi - 1) {
                int mid = (hi + lo) / 2;
                if(ans[ma[mid]] <= ans[i]) {
                    lo = mid;
                } else {
                    hi = mid;
                }
            }

            int new_l = lo + 1;
            pa[i] = ma[new_l - 1];
            ma[new_l] = i;

            l = max(l, new_l);
            l_rs[i] = l;
        }
    }

    for(int i = 0; i < m; ++i) {
        // cout << l_rs[i] << " ";
    }

    // cout << endl;
    vector<int> l_ls(m);
    {
        reverse(ans.begin(), ans.end());
        vector<int> pa(m);
        vector<int> ma(m + 1);
        int l = 0;
        for(int i = 0; i < m; ++i) {
            int lo = 0;
            int hi = l + 1;
            while(lo < hi - 1) {
                int mid = (hi + lo) / 2;
                if(ans[ma[mid]] <= ans[i]) {
                    lo = mid;
                } else {
                    hi = mid;
                }
            }

            int new_l = lo + 1;
            pa[i] = ma[new_l - 1];
            ma[new_l] = i;

            l = max(l, new_l);
            l_ls[i] = l;
        }
    }
    reverse(l_ls.begin(), l_ls.end());
    int mx = max(l_rs.back(), l_ls.front());
    for(int i = 1; i < m; ++i) {
        mx = max(mx, l_rs[i - 1] + l_ls[i]);
    }
    cout << mx << endl;
}
