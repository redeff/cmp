#include <bits/stdc++.h>
using namespace std;

vector<int> sub(vector<int> &a, vector<int> &b) {
    vector<int> total;
    for(int i = 0; i < a.size(); ++i) {
        total.push_back(a[i] - b[i]);
    }
    return total;
}

void debug(vector<int> v) {
    cerr << "[";
    for(int i = 0; i < v.size(); ++i) {
        cerr << v[i];
        if(i != v.size() - 1) cerr << " ";
    }
    cerr << "]";
}

typedef long long int ll;

const ll MOD = 1e9 + 7;
int main() {
    string s;
    cin >> s;

    int k;
    cin >> k;

    vector<vector<int>> large;
    for(int i = 0; i < k; ++i) {
        string t;
        cin >> t;

        vector<int> tc('z' - 'a' + 2, 0);
        tc['z' - 'a' + 1] = t.size();
        for(char c : t) tc[c - 'a']++;

        large.push_back(tc);
    }
    sort(large.begin(), large.end() );
    large.erase( unique( large.begin(), large.end() ), large.end() );
    // for(auto s : small) debug(s), cerr << endl;
    // cerr << endl;
    // for(auto s : large) debug(s), cerr << endl;

    vector<vector<int>> partials;
    partials.push_back(vector<int>('z' - 'a' + 2, 0));
    int n = s.size();
    for(int i = 0; i < n ; ++i) {
        auto v = partials.back();
        partials.push_back(v);
        partials.back()[s[i] - 'a']++;
        partials.back()['z' - 'a' + 1]++;
    }

    vector<ll> ns(n + 1, 0);
    ns[0] = 1;
    for(int i = 0; i < n + 1; ++i) {
        vector<int> sc('z' - 'a' + 2, 0);
        
        for(vector<int> &v : large) if(i - v.back() >= 0) { 
            /*
            cerr << i << " " << i - v.back() << endl;
            debug(partials[i - v.back()]);
            cerr << endl;
            debug(partials[i]);
            cerr << endl;
            debug(sub(partials[i], partials[i - v.back()]));
            cerr << endl;
            debug(v);
            cerr << endl;
            */
            if(sub(partials[i], partials[i - v.back()]) == v) {
                // cerr << "." << endl;
                ns[i] += ns[i - v.back()];
                ns[i] %= MOD;
            }
            // else cerr << "-" << endl;
        }
    }

    // for(int i : ns) cout << i << endl;
    cout << ns[n] << endl;
}
