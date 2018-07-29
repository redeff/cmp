#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll p = 1e9+7;

vector<ll> multiply(vector<ll> &rec, vector<ll> &a, vector<ll> &b) {
    ll k = a.size();
    vector<ll> out(2*k - 1, 0);
    for(int ai = 0; ai < k; ++ai) for(int bi = 0; bi < k; ++bi) {
        out[ai + bi] += (a[ai] * b[bi]) % p;
        out[ai + bi] %= p;
    }

    for(int oi = 2*k - 2; oi >= k; --oi) { 
        for(int ri = 0; ri < k; ++ri) {
            out[oi + ri - k] += (rec[ri] * out[oi]) % p;
            out[oi + ri - k] %= p;
        }
        out.pop_back();
    }

    return out;
}

/*
vector<ll> times10(vector<ll> rec, vector<ll> a) {
    auto a2 = multiply(rec, a, a);
    auto a4 = multiply(rec, a2, a2);
    auto a8 = multiply(rec, a4, a4);
    return multiply(rec, a2, a8);
}
*/

vector<ll> pw(vector<ll> rec, vector<ll> a, int e) {
    if(e == 0) {
        vector<ll> out(a.size(), 0);
        out[0] = 1;
        return out;
    } else if(e == 1) {
        return a;
    } else if(e == 2){
        return multiply(rec, a, a);
    } else {
        auto r = pw(rec, a, e/2);
        r = multiply(rec, r, r);
        if(e % 2 != 0) {
            r = multiply(rec, r, a);
        }

        return r;
    }
}

int main() {
    vector<ll> coeff[11] = {
        {}, // 0: dummy
        {1,0}, // 1
        {1,1,-1}, // 2
        {1,1,0,-1,-1,1}, // 3
        {1, 1, 0, 0, -2, 0, 0, 1, 1, -1}, // 4
        {1, 1, 0, 0, -1, -1, -1, 1, 1, 1, 0, 0, -1, -1, 1}, // 5
        {1, 1, 0, 0, -1, 0, -2, 0, 1, 1, 1, 1, 0, -2, 0, -1, 0, 0, 1, 1, -1}, // 6
        {1, 1, 0, 0, -1, 0, -1, -1, 0, 1, 1, 2, 0, 0, 0, -2, -1, -1, 0, 1, 1, 0, 1, 0, 0, -1, -1, 1}, // 7
        {1, 1, 0, 0, -1, 0, -1, 0, -1, 0, 1, 2, 1, 0, 1, -1, -1, -2, -1, -1, 1, 0, 1, 2, 1, 0, -1, 0, -1, 0, -1, 0, 0, 1, 1, -1}, // 8
        {1, 1, 0, 0, -1, 0, -1, 0, 0, -1, 0, 2, 1, 1, 1, 0, -1, -1, -1, -2, -1, -1, 1, 1, 2, 1, 1, 1, 0, -1, -1, -1, -2, 0, 1, 0, 0, 1, 0, 1, 0, 0, -1, -1, 1}, // 9
        {1, 1, 0, 0, -1, 0, -1, 0, 0, 0, -1, 1, 1, 1, 2, 0, 0, -1, -1, -1, -1, -3, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, -3, -1, -1, -1, -1, 0, 0, 2, 1, 1, 1, -1, 0, 0, 0, -1, 0, -1, 0, 0, 1, 1, -1} // 10
    };

    ll p = 1e9+7;
    int mx = coeff[10].size();

    vector<vector<ll>> dp(11, vector<ll>(mx+11, 0));
    dp[0][0] = 1;
    for(int k = 1; k < 11; ++k) for(int n = 1; n < mx + 11; ++n) {
        if(k-1 >= 0 && n-1 >= 0) {
            dp[k][n] += dp[k-1][n-1];
            dp[k][n] %= p;
        }
        if(n-k >= 0) {
            dp[k][n] += dp[k][n-k];
            dp[k][n] %= p;
        }
    }

    int t;
    int dummy;
    cin >> t >> dummy;
    for(int testcase = 0; testcase < t; ++testcase) {
        if(testcase % 10 == 0) {
            int k;
            string m;
            cin >> k >> m;

            int siz = coeff[k].size();
            // vector<ll> unit(siz, 0);
            // unit[1] = 1;

            vector<ll> rec = coeff[k];

            vector<ll> total(siz, 0);
            total[0] = 1;

            vector<ll> curr(siz, 0);
            curr[1] = 1;

            reverse(m.begin(), m.end());
            for(char c : m) {
                // for(auto t : curr) cerr << t;
                auto tmp = pw(rec, curr, c - '0');
                total = multiply(rec, total, tmp);
                curr = pw(rec, curr, 10);
            }

            ll fin = 0;
            for(int i = 0; i < total.size(); ++i) {
                fin += (total[i] * dp[k][i+k]) % p;
                fin %= p;
            }

            cout << fin << endl;
        } else {
            cout << 0 << endl;
        }
    }

    /*
    vector<ll> rec = {1, 1};
    vector<ll> a = {0, 1};

    for(int i = 0; i < 4; ++i) {
        a = multiply(rec, a, a, 2, 1e9+7);
    }
    */

    /*
    int k = 9;
    int n = 155555;
    vector<ll> a(coeff[k].size(), 0);
    a[1] = 1;

    vector<ll> b(coeff[k].size(), 0);
    b[0] = 1;
    for(int i = 0; i < n; ++i) {
        b = multiply(coeff[k], a, b, coeff[k].size(), 1e9+7);
    }

    ll total = 0;
    for(int i = 0; i < b.size(); ++i) {
        total += (b[i] * dp[k+1][i]) % p;
        total %= p;
    }

    cout << total << endl;
    */

    /*
    for(int i = 0; i <= 10; ++i) {
        cout << "vec![";
        for(int j = ((int) (coeff[i].size())) - 64; j < (int) coeff[i].size(); ++j) {
            if(j >= 0)
                cout << coeff[i][j] << ", ";
            else cout << "0, ";
        }
        cout << "],\n";
    }
    */
}
