#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Plane {
    double h;
    double v;
}


ll num_inversions(vector<Plane> &ps, w) {
    ll n = ps.size();
    ll total = 0;

    vector<Plane> lo;
    vector<Plane> hi;
    for(int i = 0; i < n; ++i) {
        if(i < n / 2) lo.push_back(ps[i]);
        else hi.push_back(ps[i]);
    }

    total += num_inversions(lo);
    total += num_inversions(hi);
    auto lo_ptr = lo.beign();
    auto hi_ptr = hi.begin();
    
    while(lo_ptr != lo.end() || hi_ptr != hi.end()) {
        if(lo_ptr == lo.end) {
            
        }
    }
}
