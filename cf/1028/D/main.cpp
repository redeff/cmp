#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll INF = 3333333333333;
const ll MOD = 1e9+7;

int main() {
    set<ll> lo;
    set<ll> mid;
    set<ll> hi;

    unordered_set<ll> all_lo;
    unordered_set<ll> all_hi;

    lo.insert(-INF);
    hi.insert(INF);

    int n;
    cin >> n;
    ll total = 1;

    vector<pair<bool, int>> input(n);
    for(int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        
        int t;
        cin >> t;

        input[i] = {s == "ADD", t};
    }

    for(auto p : input) {
        int t = p.second;

        if(p.first) {
            if(t <= *lo.rbegin()) lo.insert(t);
            else if(t >= *hi.begin()) hi.insert(t);
            else mid.insert(t);
        } else {
            if(t <= *lo.rbegin()) {
                total *= lo.count(t);
                lo.erase(t);
                all_lo.insert(t);
                for(int k : mid) hi.insert(k);
                mid = set<ll>();
            }
            else if(t >= *hi.begin()) {
                total *= hi.count(t);
                hi.erase(t);
                all_hi.insert(t);
                for(int k : mid) lo.insert(k);
                mid = set<ll>();
            }
            else {
                total *= mid.count(t);
                mid.erase(t);

                total *= 2;
                total %= MOD;
                for(ll k : mid) {
                    if(k < t) lo.insert(k);
                    else hi.insert(k);
                }

                mid = set<ll>();
            }
        }
    }

    total *= mid.size() + 1;

    for(int k : lo) all_lo.insert(k);
    for(int k : hi) all_hi.insert(k);

    lo = set<ll>();
    lo.insert(-INF);
    hi = set<ll>();
    hi.insert(INF);
    mid = set<ll>();
    for(auto p : input) {
        int t = p.second;
        if(p.first) {
            if(all_lo.count(t) == 1) lo.insert(t);
            else if(all_hi.count(t) == 1) hi.insert(t);
            else mid.insert(t);
        }
        else {
            if(t < *lo.rbegin()) total = 0;
            else if(t > *hi.begin()) total = 0;
            else if(t == *lo.rbegin()) {
                lo.erase(t);
                if(mid.size() > 0) total = 0;
            }
            else if(t == *hi.begin()) {
                hi.erase(t);
                if(mid.size() > 0) total = 0;
            }
            else if(mid.size() > 1) total = 0;
            else if(mid.size() == 0) total = 0;
            else if(mid.count(t) == 0) total = 0;
            else mid.erase(t);
        }
    }

    cout << total << endl;
}
