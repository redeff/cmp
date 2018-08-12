#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const ll each = 50;

int main() {
    ll c;
    cin >> c;
    unordered_set<ll> csu(c);
    for(ll ci = 0; ci < c; ++ ci) {
        ll tmp;
        cin >> tmp;
        csu.insert(tmp);
    }

    for(int i = 1; c < 2 * each - 1; ++i) {
        if(csu.count(i) == 0) {
            csu.insert(i);
            c++;
        }
    }

    vector<ll> cs;
    copy(csu.begin(), csu.end(), back_inserter(cs));
    sort(cs.begin(), cs.end());

    // c >= 2 * each + 1

    ll num = (c - (2 * each - 1)) / each;
    ll fst = c - each * num;

    // 1              -> each
    // fst - each + 1 -> fst

    ll fsta = fst - each + 1;

    vector<ll> as;
    as.push_back(max(cs[fst/2ll] - fst/2ll - 1 + fsta, fsta));
    ll ptr = fst;
    for(ll i = 0; i < num; ++i) {
        ll na = cs[ptr + each/2ll] - each/2ll;
        na = max(na, as.back() + each);
        as.push_back(na);
        ptr += each;
    }

    for(int ai = as.size() - 1; ai > 0; --ai) {
        if(as[ai] < as[ai - 1] + each) {
            as[ai - 1] = as[ai] - each;
        }
    }

    cout << as.size() + fsta - 1 << endl;
    for(int i = as.front() - fsta + 1; i < as.front(); ++i) cout << i << " ";
    for(int ae : as) cout << ae << " ";
    cout << endl;

    cout << 50 << endl;
    for(int i = 0; i < 50; ++i) {
        cout << i + 1 << " ";
    }
    cout << endl;
}
