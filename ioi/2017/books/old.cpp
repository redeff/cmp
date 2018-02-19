#include "books.h"

#include <bits/stdc++.h>
using namespace std;

long long minimum_walk(vector<int> ns, int s) {
    {
        bool all_equal = true;
        for(int i = 0; i < ns.size(); ++i) {
            if(i != ns[i]) {
                all_equal = false; break;
            }
        }
        if(all_equal) return 0;
    }

    vector<pair<int, int>> go_left;
    for(int i = 0; i < ns.size(); ++i) {
        if(ns[i] < i) {
            go_left.emplace_back(i, ns[i]);
        }
    }

    vector<pair<int, int>> fused;
    for(auto p : go_left) {
        while(!fused.empty() && fused.back().first >= p.second) {
            p.second = min(p.second, fused.back().second);
            fused.pop_back();
        }
        fused.push_back(p);
    }

    vector<bool> covered(ns.size() - 1, false);
    for(auto p : fused) {
        for(int i = p.second; i < p.first; ++i) covered[i] = true;
    }

    int lo, hi;
    for(int i = 0; true; ++i) {
        if(covered[i]) {
            lo = i;
            break;
        }
    }
    for(int i = ns.size() - 2; true; --i) {
        if(covered[i]) {
            hi = i + 1;
            break;
        }
    }

    long long int sum_of_cycles = 0;
    for(int i = 0; i < ns.size(); ++i) sum_of_cycles += abs(i - ns[i]);

    int uncovered_in_range = 0;
    for(int i = lo; i < hi; ++i) {
        if(!covered[i]) uncovered_in_range++;
    }

    long long int total = 2 * uncovered_in_range + (long long int)(sum_of_cycles);

    if(s < lo) {
        return 2 * (long long int)(lo - s) + total;
    } else if (s > hi) {
        return 2 * (long long int)(s - hi) + total;
    } else {
        return total;
    }

    /*
    for(int i = 0; i < ns.size(); ++i) cout << i << " ";
    cout << endl;
    for(int i = 0; i < ns.size(); ++i) cout << covered[i] << " ";
    cout << endl;
    */
	// return 0;
}
