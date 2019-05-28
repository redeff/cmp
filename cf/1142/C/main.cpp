#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct Point {
    ll x;
    ll y;
};

Point operator-(Point a, Point b) {
    return Point {a.x - b.x, a.y - b.y};
}

ll operator^(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

int main() {
    ll n;
    cin >> n;

    unordered_map<ll, ll> mp;
    // vector<Point> ns(n);
    for(int i = 0; i < n; ++i) {
        ll x, y;
        cin >> x >> y;
        if(mp.count(x)) {
            mp[x] = max(mp[x], y);
        }
        else mp[x] = y;
    }

    vector<Point> ns;
    for(pair<ll, ll> p : mp) ns.push_back(Point {p.first, p.second});
    for(Point &p : ns) p.y -= p.x * p.x;


    sort(ns.begin(), ns.end(), [&](Point a, Point b) {return a.x < b.x;});
    vector<Point> chull;
    for(Point p : ns) {
        while(chull.size() >= 2 && ((chull.back() - chull[chull.size() - 2]) ^ (chull.back() - p)) <= 0) {
            chull.pop_back();
        }
        chull.push_back(p);
    }
    cout << chull.size() -1 << endl;
}
