#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long int ll;

ll mn(ll a, ll b) {
    return a < b ? a : b;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> ns(n);
    for(auto &p : ns) cin >> p.first >> p.second;
    sort(ns.begin(), ns.end());

    {
        vector<pair<int, int>> chull;
        for(int i = 0; i < n; ++i) {
            while(!chull.empty() && chull.back().second < ns[i].second) {
                chull.pop_back();
            }
            chull.push_back(ns[i]);
        }
        ns = move(chull);
    }

    n = ns.size();

    vector<ll> dp(n+1);
    const ll INF = 3333333333333;
    dp[0] = 0;
    for(int i = 0; i < n; ++i) {
        dp[i+1] = INF;
        for(int j = 0; j <= i; ++j) {
            dp[i+1] = mn(
                dp[i+1],
                dp[j] + ll(ns[j].second) * ll(ns[i].first));
        }
    }

    cout << dp.back() << endl;

}