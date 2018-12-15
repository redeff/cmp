#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll MOD = 998244353ll;

ll pow2(ll n) {
    if(n == 0ll) return 1ll;
    ll rec = pow2(n / 2ll);
    if(n % 2ll == 0ll) return (rec * rec) % MOD;
    else return (2ll * rec * rec) % MOD;
}

int main() {
    ll t;
    cin >> t;
    for(ll testcase = 0ll; testcase < t; ++testcase) {
        ll n, m;
        cin >> n >> m;
        vector<vector<ll>> graph(n);
        for(ll i = 0ll; i < m; ++i) {
            ll a, b;
            cin >> a >> b;
            a--; b--;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        vector<ll> colors(n, 0ll);
        vector<ll> comps(n, 0ll);
        bool possible = true;
        function<void(ll, ll, ll)> dfs = [&](ll node, ll color, ll comp) {
            if(colors[node] == 0ll) {
                colors[node] = color;
                comps[node] = comp;
                for(ll ch : graph[node]) {
                    dfs(ch, -color, comp);
                }
            }
            else if(colors[node] != color) {
                possible = false;
                return;
            }
        };

        for(ll i = 0ll; i < n; ++i) {
            if(colors[i] == 0ll) dfs(i, 1ll, i);
        }

        vector<pair<ll, ll>> cs(n, {0ll, 0ll});
        for(ll i = 0ll; i < n; ++i) {
            if(colors[i] == 1ll) cs[comps[i]].first++;
            else cs[comps[i]].second++;
        }

        ll total = 1;
        for(ll i = 0ll; i < n; ++i) {
            if(cs[i].first == 0ll && cs[i].second == 0ll) continue;
            total *= pow2(cs[i].first) + pow2(cs[i].second);
            total %= MOD;
        }

        if(possible) cout << total;
        else cout << 0ll;
        cout << endl;
    }
}
