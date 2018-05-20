#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
    int n;
    cin >> n;

    vector<int> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i];

    vector<int> mxs(n);
    mxs[0] = ns[0] + 1;
    for(int i = 1; i < n; ++i) {
        mxs[i] = max(ns[i] + 1, mxs[i - 1]);
    }

    vector<int> min_marks(n);
    min_marks[n - 1] = mxs[n - 1];

    for(int i = n - 2; i >= 0; --i) {
        min_marks[i] = max(mxs[i], min_marks[i + 1] - 1);
    }

    /*
    for(int i = 0; i < n; ++i) cout << mxs[i] << " ";
    cout << endl;
    for(int i = 0; i < n; ++i) cout << min_marks[i] << " ";
    cout << endl;
    */

    /*
    vector<int> marks(n);
    marks[0] = 1;
    for(int i = 1; i < n; ++i) {

    }
    */

    ll total = 0;
    for(int i = 0; i < n; ++i) {
        total += (ll)(min_marks[i] - ns[i] - 1);
    }

    cout << total << endl;
}
