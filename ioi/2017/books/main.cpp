#include "books.h"

#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    int parent;
    int wei;
    int mn;
    int mx;
};

vector<UnionFind> create_union_find(int n) {
    vector<UnionFind> out(n);
    for(int i = 0; i < n; ++i) {
        out[i].parent = i;
        out[i].wei = 0;
        out[i].mn = i;
        out[i].mx = i;
    }
    return out;
}

int repr(int t, vector<UnionFind> &uf) {
    int init = t;
    while(t != uf[t].parent) {
        t = uf[t].parent;
    }
    int parent = t;
    t = init;
    while(t != uf[t].parent) {
        int next_chain = uf[t].parent;
        uf[t].parent = parent;
        t = next_chain;
    }
    return parent;
}

int join(int a, int b, vector<UnionFind> &uf) {
    int parent_a = repr(a, uf);
    int parent_b = repr(b, uf);
    if(parent_a == parent_b) return parent_a;

    if(uf[parent_a].wei == uf[parent_b].wei) {
        uf[parent_a].parent = parent_b;
        uf[parent_b].wei++;
    } else if(uf[parent_a].wei < uf[parent_b].wei) {
        uf[parent_a].parent = parent_b;
    } else {
        uf[parent_b].parent = parent_a;
    }

    int parent = repr(a, uf);
    uf[parent].mx = max(uf[parent_a].mx, uf[parent_b].mx);
    uf[parent].mn = min(uf[parent_a].mn, uf[parent_b].mn);

    return repr(a, uf);
}

void rec_join_overlapped(int a, int b, vector<UnionFind> &uf) {
    if(b - a <= 1) return;
    int mid = (a + b) / 2;
    int parent = repr(mid, uf);

    int last_sect = a;
    int times = 0;

    int fst = -1;

    for(int i = a; i < b; ++i) {
        if(repr(i, uf) == parent) {
            times++;
            rec_join_overlapped(last_sect, i, uf);
            last_sect = i + 1;
            if(fst == -1) fst = last_sect;
        }
    }

    // last_sect = a;
    unordered_set<int> all;
    unordered_set<int> ths;
    for(int i = a, j = 0; i < b && j < times - 1; ++i, ++j) {
        int p = repr(i, uf);
        if(p == parent) {
            ths = unordered_set<int>();
            // last_sect = i + 1;
        } else {
            if(ths.count(p) == 0) {
                ths.insert(p);
                if(all.count(p) == 1) {
                    join(p, mid, uf);
                } else {
                    all.insert(p);
                }
            }
        }
    }

    all = {};
    ths = {};

    for(int i = fst; i < b; ++i) {
        int p = repr(i, uf);
        if(p == parent) {
            ths = unordered_set<int>();
            // last_sect = i + 1;
        } else {
            if(ths.count(p) == 0) {
                ths.insert(p);
                if(all.count(p) == 1) {
                    join(p, mid, uf);
                } else {
                    all.insert(p);
                }
            }
        }
    }
}

bool contains(int a, int b, vector<UnionFind> &uf) {
    int pa = repr(a, uf);
    int pb = repr(b, uf);

    return uf[pa].mn < uf[pb].mn && uf[pa].mx > uf[pb].mx;
}

int extend(int p, vector<UnionFind> &uf) {
    int n = uf.size();
    p = repr(p, uf);
    if(uf[p].mn == 0 && uf[p].mx == n - 1) return 0;

    int left, right;
    left = uf[p].mn;
    right = uf[p].mx;
    while(true) {
        if(left >= 0 && contains(left, p, uf)) return uf[p].mn - left + extend(left, uf);
        if(right < n && contains(right, p, uf)) return right - uf[p].mx + extend(right, uf);
        if(left < 0 && right >= n) return n - 1 - uf[p].mx + uf[p].mn;
        left--;
        if(left >= 0) left = uf[repr(left, uf)].mn;
        right++;
        if(right < n) right = uf[repr(right, uf)].mx;
    }
}

tuple<vector<int>, int, int> convert(vector<int> ns, int s) {
    int total = 0;
    while(ns.back() == ns.size() - 1) {
        ns.pop_back();
        if(s >= ns.back()) total++, s--;
    }

    reverse(ns.begin(), ns.end());
    int n = ns.size();
    int other = 0;
    while(ns.back() == n - ns.size()) {
        other++;
        ns.pop_back();
        if(s <= n - ns.back()) total++;
        else s--;
    }
    reverse(ns.begin(), ns.end());
    for(int i = 0; i < ns.size(); ++i) ns[i] -= other;
    return make_tuple(ns, total, s);
}

long long minimum_walk(vector<int> ns, int s) {
    {
        bool all_equal = true;
        for(int i = 0; i < ns.size(); ++i) {
            if(i != ns[i]){
                all_equal = false;
                break;
            }
        }
        if(all_equal) return 0;
    }
    auto pr = convert(ns, s);
    int extra = get<1>(pr);
    ns = get<0>(pr);
    s = get<2>(pr);
    /*

    for(int i = 0; i < ns.size(); ++i) {
        cout << ns[i] << " ";
    } cout << endl;

    cout << s << endl;
    cout << extra << endl;
    */

    /*
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

    for(int i = 0; i < ns.size(); ++i) cout << i << " ";
    cout << endl;
    for(int i = 0; i < ns.size(); ++i) cout << covered[i] << " ";
    cout << endl;
	// return 0;
    */

    // Tomamos todos los ciclos como conjuntos de putnos
    // (el orden del ciclo no importa), y "unimos" dos
    // ciclos si los intervalos mínimos que los contienen
    // se superponen pero no están nested
    //
    // Esto hace que luego de unir, los conjuntos ("ciclos")
    // formen un árbol, con ciclos a dentro de otros ciclos
    //
    // disjoint_set_ds <- disjoint sets {0}, {1}, ..., {n - 1}
    // for (k, indx) in ns
    //     join k and indx in disjoint_set_ds
    //
    // do the fo
    //

    int sum_cycles = 0;
    for(int i = 0; i < ns.size(); ++i) {
        sum_cycles += abs(ns[i] - i);
    }

    auto n = ns.size();
    auto uf = create_union_find(n);
    for(int i = 0; i < n; ++i) {
        join(i, ns[i], uf);
    }
    rec_join_overlapped(0, n, uf);

    for(int i = 0; i < n; ++i) {
        // cout << repr(i, uf) << " ";
    }

    int pat = extend(s, uf);
    // cout << pat << endl;

    return sum_cycles + (long long int)(extra * 2 + pat * 2);
}
