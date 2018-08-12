#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i];

    vector<int> ord(n);
    for(int i = 0; i < n; ++i) ord[i] = i;
    sort(ord.begin(), ord.end(), [&](int a, int b){return ns[a] < ns[b];});

    set<int> bears = {-1, n};
    multiset<int> gaps;
    gaps.insert(n);

    vector<ll> xs;
    for(int i = 0; i < n; ++i) {
        bears.insert(ord[i]);
        auto p = bears.find(ord[i]);
        gaps.erase(gaps.find(*next(p) - *prev(p) - 1));
        gaps.insert(*next(p) - *p - 1);
        gaps.insert(*p - *prev(p) - 1);
        while(n - xs.size() > *gaps.rbegin()) {
            xs.push_back(ns[ord[i]]); 
        }
    }

    reverse(xs.begin(), xs.end());
    for(ll x : xs) cout << x << " ";
    cout << endl;
}
