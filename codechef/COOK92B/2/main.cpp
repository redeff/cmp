#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 2000000000;

void doit() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> mat(m, vector<ll>(n));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
           cin >> mat[j][i]; 
        }
    }

    reverse(mat.begin(), mat.end());
    for(auto &v : mat) {
        reverse(v.begin(), v.end());
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(mat[j][i] == -1) {
                ll mx = INF;
                if(j > 0) mx = min(mx, mat[j - 1][i]);
                if(i > 0) mx = min(mx, mat[j][i - 1]);
                mat[j][i] = mx;
            }
        }
    }

    reverse(mat.begin(), mat.end());
    for(auto &v : mat) {
        reverse(v.begin(), v.end());
    }

    bool works = true;
    for(int i = 0; i < n; ++i) {
        for(int j = 1; j < m; ++j) {
            if(mat[j - 1][i] > mat[j][i]) works = false;
        }
    }

    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(mat[j][i - 1] > mat[j][i]) works = false;
        }
    }

    if(!works) {
        cout << "-1" << endl;
    } else {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
               cout << mat[j][i] << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    int T;
    cin >> T;
    for(int i = 0; i < T; ++i) {
        doit();
    }
}
