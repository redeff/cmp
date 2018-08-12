#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

typedef int T;
T op(T a, T b) {return a + b;}
T zero = 0;
#include "../../../rec/segment/lib.h"

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<ll> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i];

    vector<int> ord(n);
    for(int i = 0; i < n; ++i) ord[i] = i;
    sort(ord.begin(), ord.end(), [&](int a, int b) {return ns[a] < ns[b];});
    vector<int> heads = {0};
    for(int i = 0; i < n; ++i) {
        heads.push_back(update(heads.back(), ord[i], 1));
    }

    /*
    for(int i = 0; i < n; ++i) {
        debug(heads[i], st); cerr << endl;
        cerr << i << " - ";
        for(int j = 0; j < n; ++j) {
            cerr << query(heads[i], BIG + j, st) << " ";
        }
        cerr << endl;
    }
    */

    for(int i = 0; i < m; ++i) {
        int a, b, k;
        cin >> a >> b >> k;
        a--; b--;

        int lo = 0;
        int hi = n;

        while(hi - lo > 1) {
            int mid = (hi + lo) / 2;
            int amount = query(heads[mid], b);
            amount -= query(heads[mid], a - 1);
            if(amount < k) lo = mid;
            else hi = mid;
        }

        cout << ns[ord[lo]] << endl;
    }
}
