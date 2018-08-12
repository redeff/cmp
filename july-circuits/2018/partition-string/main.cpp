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

void debug(vector<int> &v) {
    cerr << "[";
    for(int i = 0; i < v.size(); ++i) {
        cerr << v[i];
        if(i != v.size() - 1) cerr << " ";
    }
    cerr << "]";
}

int main() {
    string s;
    cin >> s;

    int k;
    cin >> k;

    int sq = 316;

    unordered_set<vector<int>, VectorHash> small;
    vector<vector<int>> large;
    for(int i = 0; i < k; ++i) {
        string t;
        cin >> t;

        vector<int> tc('z' - 'a' + 2, 0);
        tc['z' - 'a' + 1] = t.size();
        for(char c : t) tc[c - 'a']++;

        if(t.size() < sq) {
            small.insert(tc);
        } else {
            large.push_back(tc);
        }
    }
    sort(large.begin(), large.end() );
    large.erase( unique( large.begin(), large.end() ), large.end() );
    vector<vector<int>> partials;
    partials.push_back(vector<int>('z' - 'a' + 2, 0));
    int n = s.size();
    for(int i = 0; i < n ; ++i) {
        partials.push_back(partials.back());
        partials.back()[s[i] - 'a']++;
        partials.back()['z' - 'a' + 1]++;
    }

    vector<ll> ns(n + 1, 0);
    ns[0] = 1;
    for(int i = 0; i < n + 1; ++i) {
        vector<int> sc('z' - 'a' + 2, 0);
        // sc['z' - 'a' + 1] = 
        for(int j = i - 1; i - j < sq && j >= 0; --j) {
            sc['z' - 'a' + 1]++;
            sc[s[j] - 'a']++; 
            // debug(sc);
            if(small.count(sc)){
                // cerr << ".";
                ns[i] += ns[j];
                ns[i] %= MOD;
            }
            // cerr << endl;
        } 


        for(vector<int> &v : large) if(i - v.back() >= 0) { 
            if(sub(partials[i], partials[i - v.back()]) == v) {
                ns[i] += ns[i - v.back()];
                ns[i] %= MOD;
            }
        }
    }

    // for(int i : ns) cout << i << endl;
    cout << ns[n] << endl;
}
