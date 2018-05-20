#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const ll MOD = 33333333;
const ll INF = 3333333333;

struct Interval {
    ll s;
    mutable ll e;
    bool inc;

    Interval(ll s, ll e, bool inc): s(s), e(e), inc(inc) {}
    Interval() {}

};

#define test(lala, lolo) if(lala < lolo) return true; else if(lala > lolo) return false;

bool operator<(Interval a, Interval b) {
    // return a.s < b.s;
    test(a.s, b.s);
    test(a.e, b.e);
    test(a.inc, b.inc);
    return false;
}

void doit() {
    ll n, m, k;
    cin >> n >> m >> k;

    vector<ll> ns(n);
    vector<Interval> ms(m);

    for(ll i = 0; i < n; ++i) {
        cin >> ns[i];
    }

    for(ll i = 0; i < m; ++i) {
        string t;
        cin >> t;
        ms[i].inc = t == "I";
        cin >> ms[i].s;
        ms[i].s--;
        cin >> ms[i].e;
        ms[i].e--;
    }

    sort(ms.begin(), ms.end());

    vector<ll> nxt(n, 0);
    ll last_end = 0;
    for(ll i = 0; i < m; ++i) {
        for(ll j = max(last_end, ms[i].s); j < ms[i].e; ++j) {
            ll prv = nxt[j];
            if(ms[i].inc) nxt[j] = 1; else nxt[j] = -1;
            if(prv != 0 && prv != nxt[j]) {
                cout << 0 << endl;
                return;
            }
        }
        last_end = max(last_end, ms[i].e);
    }

    vector<pair<ll, ll>> sects;
    for(ll i = 0; i < n; ++i) {
        if(i == 0 || nxt[i - 1] == 0) {
            sects.emplace_back(i, i + 1);         
        } else {
            sects.back().second++;
        }
    }

    for(int i = 0; i < n; ++i) cout << ns[i] << " ";
    cout << " ns\n";

    for(int i = 0; i < n; ++i) cout << nxt[i] << " ";
    cout << " ns\n";

    for(int i = 0; i < sects.size(); ++i) cout << sects[i].first << " " << sects[i].second << " ; ";
    cout << " sects\n";

    ll total = 1;
    for(auto p : sects) {
        cout << "sect" << endl;
        bool stable = false;
        for(ll i = p.first; i < p.second; ++i) {
            if(ns[i] != -1) stable = true;
        }
        
        ll mx = -INF;
        ll mn = INF;
        ll sm = 0;

        for(ll i = p.first; i < p.second; ++i) {
            cout << "ran " << i << endl;
            mx = max(mx, sm);
            mn = min(mn, sm);
            sm += nxt[i];
        }

        cout << mx << " ~ " << mn << endl;

        if(stable) {
            ll start = -1;
            ll sm = 0;
            for(ll i = p.first; i < p.second; ++i) {
                if(ns[i] != -1) {
                    if(start == -1) start = ns[i] - sm;
                    else if(ns[i] - sm != start) {
                        cout << 0 << endl;
                        return;
                    }
                } 
                sm += nxt[i];
            }

            if(start + mx > k || start - mn <= 0) {
                cout << 0 << endl;
                return;
            }
        } else {
            cout << "oo " << k - (mx - mn) << endl;
            ll delta = k - (mx - mn);
            if(delta <= 0) total = 0;
            else total *= k - (mx - mn);
            total = total % MOD;
        }
    }

    cout << "total: ";
    cout << total << endl;

    /*
    vector<Interval> new_ms = {ms[0]};
    for(int i = 1; i < m; ++i) {
        if(ms[i].s < new_ms.back().e) {
            if(ms[i].inc != new_ms.back().inc) { cout << -1 << endl; return; }
            new_ms.back().e = max(new_ms.back().e, ms[i].e);
        } else {
            new_ms.push_back(ms[i]);
        }
    }

    m = new_ms.size();
    ms = move(new_ms);

    vector<bool> stable(m, false);
    vector<int> start(m, -1);
    vector<bool> visited(n, false);

    for(int i = 0; i < m; ++i) {
        for(int j = ms[i].s; j < ms[i].e; ++j) {
            if(ns[j] != -1) {
                start[i] = ns[j] - j + ms[i].s;
                stable[i] = true;
            }
            visited[j] = true;
        }
    }

    ll total = 1;
    for(int i = 0; i < m; ++i) {
        if(stable[i]) {
            if(start[i] <= 0) {
                total = 0;
                cout << "oops" << endl;
            }
            if(start[i] + ms[i].e - ms[i].s > k) {
                total = 0;
                cout << "aaps" << endl;
            }
        } else {
            total *= ll(k - (ms[i].e - ms[i].s));
            total = total % MOD;
        }
    }

    for(int i = 0; i < n; ++i) {
        if(ns[i] == -1 && !visited[i]) {
            total *= ll(k);
            total = total % MOD;
        }
    }

    cout << total << endl;
    return;

fal: cout << 0 << endl;
     */

    /*
    set<Interval> ms;

    auto curr = ms.begin();
    while(next(curr) != ms.end()) {
        if(next(curr)->s > curr->e) curr = next(curr);
        else {
            if(curr->inc != next(curr) -> inc) goto fal;
            else {
                curr->e = max(curr->e, next(curr)->e);
                ms.erase(next(curr));
            }
        }
    }

    vector<bool> stable(ms.size(), false);
    vector<bool> visited(n, false);

    for(int i = 0, auto ptr = ms.begin(); i < ms.size(); i++, ptr++) {
        for(int j = ptr->s; j < ptr->e) {
            if(ns[j] != -1) stable[i] = true;
            visited[j] = true;
        }
    }

    for(
    */
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cout << "----------------------------" << endl;
        doit();
    }
}
