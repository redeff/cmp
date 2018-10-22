#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;

const int BOUND = 150000;
const ll MOD = 1000000007;

int main() {
    int t;
    cin >> t;

    vector<ll> facts(BOUND, -1);
    facts[0] = 1;
    for(ll i = 1; i < BOUND; ++i) {
        facts[i] = (2ll*i - 1ll) * facts[i-1ll];
        facts[i] %= MOD;
    }

    for(int lala = 0; lala < t; ++lala) {
        int n;
        cin >> n;
        vector<int> ns(n);
        for(int i = 0; i < n; ++i) cin >> ns[i];
        sort(ns.begin(), ns.end());

        vector<ll> amount {1};
        for(int i = 1; i < n; ++i) {
            if(ns[i - 1] == ns[i]) amount.back()++;
            else amount.push_back(1);
        }

        ll total = 1;
        int curr = 0;
        for(ll a : amount) {
            if(a % 2 == 1 || curr % 2 == 1) {
                total *= a;
                total %= MOD;
            }

            total *= facts[a/2];
            total %= MOD;

            curr += a;
        }

        cout << total << endl;
    }
}
