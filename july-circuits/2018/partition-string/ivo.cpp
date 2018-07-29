#include <bits/stdc++.h>
using namespace std;

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

vector<int> sub(vector<int> &a, vector<int> &b) {
    vector<int> total;
    for(int i = 0; i < a.size(); ++i) {
        total.push_back(a[i] - b[i]);
    }
    return total;
}

typedef long long int ll;
const ll MOD = 1e9 + 7;

int main() {
    string s;
    cin >> s;

    int k;
    cin >> k;

    vector<vector<int>> vecs;
    vector<int> lens;
    for(int i = 0; i < k; ++i) {
        string t;
        cin >> t;

        vector<int> tc('z' - 'a' + 1, 0);
        for(char c : t) tc[c - 'a']++;
        vecs.push_back(tc);
        lens.push_back(t.size());
    }

    sort(lens.begin(), lens.end());
    lens.erase(unique(lens.begin(), lens.end()), lens.end());

    vector<unordered_set<vector<int>, VectorHash>> segs(lens.size());
    for(auto v : vecs) {
        int len = 0;
        for(int i : v) len += i;
        int index = lower_bound(lens.begin(), lens.end(), len) - lens.begin();
        segs[index].insert(v);
    }

    // for(auto s : small) debug(s), cerr << endl;
    // cerr << endl;
    // for(auto s : large) debug(s), cerr << endl;

    vector<vector<int>> partials;
    partials.push_back(vector<int>('z' - 'a' + 1, 0));
    int n = s.size();
    for(int i = 0; i < n ; ++i) {
        partials.push_back(partials.back());
        partials.back()[s[i] - 'a']++;
    }

    vector<ll> ns(n + 1, 0);
    ns[0] = 1;
    for(int k = 0; k < n + 1; ++k) {
        for(int i = 0; i < lens.size(); ++i) if(k - lens[i] >= 0) {
            if(segs[i].count(sub(partials[k], partials[k - lens[i]]))) {
                ns[k] += ns[k - lens[i]];
                ns[k] %= MOD;
            }
        }
    }

    // for(int i : ns) cout << i << endl;
    cout << ns[n] << endl;
}
