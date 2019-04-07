#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long int ll;

ll mn(ll a, ll b) {
    return a < b ? a : b;
}

struct Point {
    ll x;
    ll y;
    Point operator-(Point a) {
        a.x = x - a.x;
        a.y = y - a.y;
        return a;
    }
};

ll cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

ll dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

int main() {
    ll n;
    cin >> n;
    vector<Point> ns(n);
    for(auto &p : ns) cin >> p.x >> p.y;
    sort(ns.begin(), ns.end(), [&](Point a, Point b) {
        if(a.x != b.x) return a.x < b.x;
        if(a.y != b.y) return a.y < b.y;
        return false;
    });

    {
        vector<Point> chull;
        for(ll i = 0; i < n; ++i) {
            while(!chull.empty() && chull.back().y <= ns[i].y) {
                chull.pop_back();
            }
            chull.push_back(ns[i]);
        }
        ns = move(chull);
    }

    vector<Point> chull;
    n = ns.size();

    vector<ll> dp(n+1);
    const ll INF = 3333333333333;
    dp[0] = 0;
    for(ll i = 0; i < n; ++i) {
        dp[i+1] = dp[i] + ns[i].x * ns[i].y;
        if(!chull.empty()) {
            ll lo = 0;
            ll hi = chull.size()-1;
            while(hi - lo > 1) {
                ll mid = (hi + lo) / 2;
                Point m = chull[mid] - chull[mid-1];
                Point test = {ns[i].x, -1};
                if(dot(test, m) > 0) lo = mid;
                else hi = mid;
            }
            Point m = chull[hi];
            dp[i+1] = mn(dp[i+1], m.x * ns[i].x - m.y);
        }

        Point add = {ns[i].y, -dp[i]};
        while(chull.size() >= 2) {
            Point last = chull[chull.size()-1];
            Point pre = chull[chull.size()-2];
            last = last - add;
            pre = pre - add;
            if(cross(last, pre) < 0) {
                chull.pop_back();
            } else {
                break;
            }
        }
        chull.push_back(add);
    }

    cout << dp.back() << endl;

}