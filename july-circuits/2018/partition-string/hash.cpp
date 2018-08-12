#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MOD = 1e9 + 7;

int main() {
    string s;
    cin >> s;

    int k;
    cin >> k;

    vector<ll> rands('z' - 'a' + 1);
    srand(912840);
    for(int i = 0; i < 'z' - 'a'; ++i) {
        rands[i] = (ll) rand() * (ll) rand();
    }

    vector<pair<ll, int>> vecs;
    vector<int> lens;
    for(int i = 0; i < k; ++i) {
        string t;
        cin >> t;

        ll tc = 0;
        for(char c : t) {
            tc += rands[c - 'a'];
        }
        vecs.push_back({tc, t.size()});
        lens.push_back(t.size());
    }

    sort(lens.begin(), lens.end());
    lens.erase(unique(lens.begin(), lens.end()), lens.end());

    vector<unordered_set<ll>> segs(lens.size());
    for(auto v : vecs) {
        int index = lower_bound(lens.begin(), lens.end(), v.second) - lens.begin();
        segs[index].insert(v.first);
    }

    // for(auto s : small) debug(s), cerr << endl;
    // cerr << endl;
    // for(auto s : large) debug(s), cerr << endl;

    vector<ll> partials;
    partials.push_back(0);
    int n = s.size();
    for(int i = 0; i < n ; ++i) {
        partials.push_back(partials.back());
        // partials.back()[s[i] - 'a']++;
        partials.back() += rands[s[i] - 'a'];
    }

    vector<ll> ns(n + 1, 0);
    ns[0] = 1;
    for(int k = 0; k < n + 1; ++k) {
        for(int i = 0; i < lens.size(); ++i) if(k - lens[i] >= 0) {
            if(segs[i].count(partials[k] - partials[k - lens[i]])) {
                ns[k] += ns[k - lens[i]];
                ns[k] %= MOD;
            }
        }
    }

    // for(int i : ns) cout << i << endl;
    cout << ns[n] << endl;
}
