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

void join_diff_sects(vector<pair<int, int>> sects, int join_with, vector<UnionFind> &uf) {
    unordered_set<int> all;
    unordered_set<int> ths;

    for(auto p : sects) {
        for(int i = p.first; i < p.second; ++i) {
            if(ths.count(i) == 0) {
                ths.insert(i);
                if(all.count(i) == 1) {
                    join(i, join_with, uf);
                } else {
                    all.insert(i);
                }
            }
        }
    }
}

void rec_join_overlapped(int a, int b, vector<UnionFind> &uf) {
    if(b - a <= 1) return;
    int mid = (a + b) / 2;
    int parent = repr(mid, uf);

    /*
    int last_sect = a;
    int times = 0;

    int fst = -1;
    */

    vector<pair<int, int>> sections;
    sections.emplace_back(a, -1);

    for(int i = a; i < b; ++i) {
        if(repr(i, uf) == parent) {
            sections.back().second = i;
            sections.emplace_back(i + 1, -1);
            /*
            times++;
            rec_join_overlapped(last_sect, i, uf);
            last_sect = i + 1;
            if(fst == -1) fst = last_sect;
            */
        }
    }
    sections.back().second = b;

    for(auto p : sections) {
        rec_join_overlapped(p.first, p.second, uf);
    }

    vector<pair<int, int>> fsts(sections.begin(), sections.end() - 1);
    vector<pair<int, int>> snds(sections.begin() + 1, sections.end());

    join_diff_sects(fsts, mid, uf);
    join_diff_sects(snds, mid, uf);

    // rec_join_overlaped(last_sect, b, uf);

    // last_sect = a;
    /*
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
    */
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
    int total_l = 0;
    int total_r = 0;
    while(true) {
        if(left >= 0 && contains(left, p, uf)) return total_l + extend(left, uf);
        if(right < n && contains(right, p, uf)) return total_r + extend(right, uf);
        if(left < 0 && right >= n) return total_l + total_r;
        left--;
        if(left >= 0) {
            left = uf[repr(left, uf)].mn;
            total_l++;
        }
        right++;
        if(right < n) {
            right = uf[repr(right, uf)].mx;
            total_r++;
        }
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

const int INF = 333333333;

bool is_in(pair<int, int> p, int x) {
    int lo = p.first;
    int hi = p.second;
    return (lo < hi) ? (lo <= x && x <= hi) : (x <= hi || lo <= x);
}

vector<int> remove_unique(vector<int> &ns) {
    unordered_map<int, int> amount;
    for(int i = 0; i < ns.size(); ++i) {
        ++amount[ns[i]];
    }

    vector<int> out;
    for(int i = 0; i < ns.size(); ++i) {
        if(amount[ns[i]] > 1) out.push_back(ns[i]);
    }

    return out;
}

pair<pair<int, int>, int> merge_bounds(pair<int, int> a, pair<int, int> b) {
    int covered = 0;
    int lo = is_in(a, b.first) ? (covered |= 1, a.first) : b.first;
    int hi = is_in(a, b.second) ? (covered |= 2, a.second) : b.second;
    return {{lo, hi}, covered};
}

void recursive(vector<int> ns, vector<UnionFind> &out) {
    cerr << "Enter" << endl;

    for(int i : ns) {
        cout << i << " ";
    } cout << endl;

    // Remove sets that consist of single elements
    // beacuse they can't be joined with anything
    ns = remove_unique(ns);
    int n = ns.size();

    for(int i : ns) {
        cout << i << " ";
    } cout << endl;

    if(n == 0) return;

    auto dist = [&](int a, int b) {
        if(a == b) return 0;
        else if(a < b) return b - a;
        else return n + b - a;
    };

    unordered_map<int, vector<int>> sets;
    for(int i = 0; i < n; ++i) {
        sets[ns[i]].push_back(i);
    }

    unordered_map<int, pair<int, int>> extremes;
    for(const auto &p : sets) {
        const auto &v = p.second;
        int index = p.first;

        int mx = -INF;
        int mxf;
        int mxs;

        for(int i = 0; i < v.size(); ++i) {
            int nxt = (i == v.size() - 1) ? 0 : (i + 1);
            int ds = dist(v[i], v[nxt]);
            if(mx < ds) {
                mx = ds;
                mxs = v[i];
                mxf = v[nxt];
            }
        }

        extremes[index] = {mxf, mxs};
    }

    for(auto p : extremes) {
        cerr << p.first << " " << p.second.first << " " << p.second.second << endl;
    }

    int edge = -1;
    int init = 0;
    vector<pair<int, int>> sects;
    while(init != edge) {
        // cout << "once" << endl;
        // cout << init << endl;
        unordered_set<int> colors;
        colors.insert(ns[init]);
        pair<int, int> bounds = extremes[ns[init]];
        // cout << bounds.first << endl;
        // cout << bounds.second << endl;

        int left_ptr = init;
        int right_ptr = init;

        while(true) {
            /*
            if(is_in(bounds, left_ptr)) {
                left_ptr--;
                // cerr << "Decr" << endl;
                if(left_ptr < 0) left_ptr += n;
            }

            if(is_in(bounds, right_ptr)) {
                right_ptr++;
                // cerr << "Incr" << endl;
                if(right_ptr >= n) right_ptr -= n;
            }
            */

            int pre = left_ptr;
            left_ptr--;
            if(left_ptr < 0) left_ptr += n;
            if(!is_in(bounds, left_ptr)) left_ptr = pre;

            pre = right_ptr;
            right_ptr++;
            if(right_ptr >= n) right_ptr -= n;
            if(!is_in(bounds, right_ptr)) right_ptr = pre;

            auto add_bound = [&](int color) {
                int covered;
                tie(bounds, covered) = merge_bounds(bounds, extremes[color]);
                if(covered == 0) {
                    // colors = {ns[left_ptr]};
                    colors = unordered_set<int>();
                    colors.insert(ns[left_ptr]);
                } else if(covered != 3) {
                    colors.insert(ns[left_ptr]);
                }
 
            };

            auto recurse_big_enough = [&]() {
                vector<pair<int, int>> sections;
                // for(int i = 1; i < colors.size(); ++i) {
                //     out.emplace_back(colors[i], colors[i - 1]);
                // }
                for(auto it = colors.begin(); next(it) != colors.end(); ++it) {
                    // out.emplace_back(*it, *next(it));
                    join(*it, *next(it), out);
                }

                sections.emplace_back(-1, -1);
                for(int i = 0; i < n; ++i) {
                    if(colors.count(ns[i]) > 0) {
                        sections.back().second = i;
                        sections.push_back({i + 1, -1});
                    }
                }

                sections.front().first = sections.back().first;
                sections.pop_back();

                unordered_set<int> all;
                for(auto bound : sections) {
                    unordered_set<int> ths;
                    vector<int> rec;
                    for(int i = bound.first; i != bound.second; ++i) {
                        if(i >= n) i -= n;
                        if(i == bound.second) break;

                        int color = ns[i];

                        if(ths.count(color) == 0) {
                            ths.insert(color);
                            if(all.count(color) == 1) {
                                // out.emplace_back(color, *colors.begin());
                                join(color, *colors.begin(), out);
                            } else {
                                all.insert(color);
                            }
                        }

                        rec.push_back(ns[i]);
                    }

                    cout << "rec call" << endl;
                    recursive(rec, out);
                    cout << "rec recall" << endl;
                }
            };

            add_bound(ns[left_ptr]);
            if(dist(bounds.first, bounds.second) >= n/2) {
                recurse_big_enough();
                return;
            }

            add_bound(ns[right_ptr]);
            if(dist(bounds.first, bounds.second) >= n/2) {
                recurse_big_enough();
                return;
            }

            if(left_ptr == bounds.first && right_ptr == bounds.second) {
                init = right_ptr + 1;
                if(init >= n) init -= n;

                if(edge == -1) edge = left_ptr;
                // cerr << edge << endl;
                sects.emplace_back(left_ptr, init);
                break;
            } else {
                // cout << left_ptr << " " << right_ptr << endl;
            }
            // cerr << left_ptr << " " << bounds.first << endl;
            // cerr << right_ptr << " " << bounds.second << endl;
        }
    }

    for(auto bound : sects) {
        vector<int> rec;
        for(int i = bound.first; i != bound.second; ++i) {
            if(i >= n) i -= n;
            if(i == bound.second) break;
            rec.push_back(ns[i]);
        }

        recursive(rec, out);
    }

    cerr << "Close" << endl;
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

    // rec_join_overlapped(0, n, uf);
    vector<int> colors;
    for(int i = 0; i < uf.size(); ++i) {
        colors.push_back(repr(i));
    }
    recursive(colors, uf);

    for(int i = 0; i < n; ++i) {
        // cerr << repr(i, uf) << " ";
    }

    int pat = extend(s, uf);
    // cout << pat << endl;

    return sum_cycles + (long long int)(extra * 2 + pat * 2);
}
