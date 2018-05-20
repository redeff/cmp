#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
    int n, q;
    cin >> n >> q;
    vector<ll> ns(n), qs(q);

    for(int i = 0; i < n; ++i) cin >> ns[i];
    for(int i = 0; i < q; ++i) cin >> qs[i];

    vector<ll> sums(n + 1);
    sums[0] = 0;

    for(int i = 0; i < n; ++i) {
        sums[i + 1] = sums[i] + ns[i];
    }

    int curr_dead = 0;
    ll arrows_shot = 0;

    for(int i = 0; i < q; ++i) {
        arrows_shot += qs[i];
        curr_dead = distance(sums.begin(), upper_bound(sums.begin(), sums.end(), arrows_shot)) - 1;
        // cerr << "c: " << curr_dead << endl;
        if(curr_dead >= n) {
            curr_dead = 0;
            arrows_shot = 0;
        }

        cout << n - curr_dead << endl;
    }
}
