#include <bits/stdc++.h>
using namespace std;

bool is_in(pair<int, int> p, x) {
    if(p.first < p.second) {
        return p.first <= x && x < p.second;
    } else {
        return x <= p.second || p > p.first;
    }
}

void join_sets(vector<int> disjoint_sets, vector<pair<int, int>> out) {
    int n = disjoint_sets.size();
    unordered_map<int, vector<int>> sets;
    for(int i = 0; i < n; ++i) {
        sets[disjoint_sets[i]].push_back(i);
    } 

    // TODO: Hasndle single element vectors
    auto iter = find_if(sets.begin(), sets.end(), [&](const vector<int> v) {
            for(int i = 1; i < v.size(); ++i) {
                if(v[i] - v[i - 1] > n/2) {
                    return false;
                }
            }          
            
            if(n - (v.back() - v[0]) > n/2) {
                return false;
            }

            return true;
        }
    );

    if(iter == sets.end()) {
        list<pair<int, int>> bounds;
        for(auto it : sets) {
            int index = it.first;
            const vector<int> &v = it.second;

            for(int i = 0; i < v.size(); ++i) {
                if(v[i] - v[i - 1] > n/2) {
                    bounds.emplace_back(v[i - 1], v[i]);
                    goto end;
                }
            }

            if(n - (v.back() - v[0]) > n/2) {
                bounds.emplace_back(v[0], v.back());
                goto end;
            }
end:
            ;
        }

        bounds.sort([&](pair<int, int> a, pair<int, int> b) {
                return a.second < b.second;
            }
        );

        for(auto it = bounds.begin(); it != bounds.end(); ++it) {
            while(it != bounds.begin() && is_in(*it, it.prev()->second)) {
                if(!is_in(*it, it.prev()->first)) {
                    it->first = it.prev().first;
                }

                bounds.erase(it.prev());
            }
        }

        while()

    } else {
    }
}
