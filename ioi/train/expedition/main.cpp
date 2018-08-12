#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Stop {
    ll dist;
    ll fuel;
};

bool operator<(Stop a, Stop b) {
    return a.dist < b.dist;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int testcase;
    cin >> testcase;
    for(; testcase; --testcase) {
        int n;
        cin >> n;
        
        n++;
        vector<Stop> ns(n);
        for(int i = 0; i < n; ++i) cin >> ns[i].dist >> ns[i].fuel;

        sort(ns.begin(), ns.end());


        ll pos = ns.back().dist;
        priority_queue<ll> best;

        int total = -1;
        while(pos > 0) {
            while(ns.back().dist >= pos) {
                best.push(ns.back().fuel);
                ns.pop_back();
            }
            
            if(best.empty()) {
                total = -1;
                break;
            } 

            pos -= best.top();
            best.pop();
            total++;
        }

        cout << total << endl;
    }
}
