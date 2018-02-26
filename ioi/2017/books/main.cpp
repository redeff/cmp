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

void join(int a, int b, vector<UnionFind> &uf) {
    int parent_a = repr(a, uf);
    int parent_b = repr(b, uf);
    if(parent_a == parent_b) return;

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
}
bool contains(int a, int b, vector<UnionFind> &uf) {
    int pa = repr(a, uf);
    int pb = repr(b, uf);

    return uf[pa].mn < uf[pb].mn && uf[pa].mx > uf[pb].mx;
}

int extend(int p, vector<UnionFind> &uf) {
    int n = uf.size();
    p = repr(p, uf);
    if(uf[p].mn == 0 && uf[p].mx == n - 1) {
        // cout << "crach" << endl;
        return 0;
    }
    // cout << "oops" << endl;

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
        if(s >= ns.size()) total++, s--;
    }

    reverse(ns.begin(), ns.end());
    int n = ns.size();
    int other = 0;
    while(ns.back() == n - ns.size()) {
        other++;
        ns.pop_back();
        // if(s <= n - ns.back()) total++;
        // else s--;
        --s;
        if(s < 0) {
            s = 0;
            total++;
        }
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
    // cerr << ">\n";
    // Remove sets that consist of single elements
    // beacuse they can't be joined with anything
    ns = remove_unique(ns);
    int n = ns.size();

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

    int init = 0;
    vector<pair<int, int>> sects;
    vector<bool> red(n, false);
    while(!red[init]) {
        // cout << "once" << endl;
        // cout << init << endl;
        unordered_set<int> colors;
        colors.insert(ns[init]);
        pair<int, int> bounds = extremes[ns[init]];
        // cout << bounds.first << endl;
        // cout << bounds.second << endl;

        int left_ptr = init;
        int right_ptr = init;

        auto recurse_big_enough = [&]() {
            vector<pair<int, int>> sections;
            // for(int i = 1; i < colors.size(); ++i) {
            //     out.emplace_back(colors[i], colors[i - 1]);
            // }
            for(auto it = colors.begin(); next(it) != colors.end(); ++it) {
                // out.emplace_back(*it, *next(it));
                join(*it, *next(it), out);
            }

            for(auto c : colors){
                // cerr << "color " << c << endl;
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

            for(auto bound : sections) {
                // cerr << bound.first << " " << bound.second << endl;
            }

            unordered_set<int> mixed;

            int rk = 10943;
            int * rnd = &rk; 
            unordered_set<int> all;
            for(auto bound : sections) {
                // cerr << rnd << " " << bound.first << " " << bound.second << endl;
                unordered_set<int> ths;
                // vector<int> rec;
                for(int i = bound.first; i != bound.second; ++i) {
                    if(i >= n) i -= n;
                    if(i == bound.second) break;

                    int color = ns[i];

                    if(ths.count(color) == 0) {
                        ths.insert(color);
                        if(all.count(color) == 1) {
                            // out.emplace_back(color, *colors.begin());
                            join(color, *colors.begin(), out);
                            mixed.insert(color);
                            // cerr << rnd << " gain " << color << endl;
                        } else {
                            // cerr << rnd << " loose " << color << endl;
                            all.insert(color);
                        }
                    }

                    // rec.push_back(ns[i]);
                }

                // recursive(rec, out);
            }

            for(auto bound : sections) {
                vector<int> rec;
                for(int i = bound.first; i != bound.second; ++i) {
                    if(i >= n) i -= n;
                    if(i == bound.second) break;
                    rec.push_back(ns[i]);
                    if(mixed.count(rec.back()) > 0) {
                        rec.back() = *mixed.begin();
                    }
                }

                if(!mixed.empty()) {
                    rec.push_back(*mixed.begin());
                }

                recursive(rec, out);
            }
        };

        while(true) {

            red[left_ptr] = true;
            int pre = left_ptr;
            left_ptr--;
            if(left_ptr < 0) left_ptr += n;
            if(!is_in(bounds, left_ptr)) left_ptr = pre;
            red[left_ptr] = true;

            red[right_ptr] = true;
            pre = right_ptr;
            right_ptr++;
            if(right_ptr >= n) right_ptr -= n;
            if(!is_in(bounds, right_ptr)) right_ptr = pre;
            red[right_ptr] = true;

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
            add_bound(ns[left_ptr]);
            if(dist(bounds.first, bounds.second) >= n/2) {
                recurse_big_enough();
                // cerr << "<\n";
                return;
            }

            add_bound(ns[right_ptr]);
            if(dist(bounds.first, bounds.second) >= n/2) {
                recurse_big_enough();
                // cerr << "<\n";
                return;
            }

            if(left_ptr == bounds.first && right_ptr == bounds.second) {
                init = right_ptr + 1;
                if(init >= n) init -= n;

                sects.emplace_back(left_ptr, init);
                break;
            } else {
                // cout << left_ptr << " " << right_ptr << endl;
            }
            // cerr << left_ptr << " " << bounds.first << endl;
            // cerr << right_ptr << " " << bounds.second << endl;
        }
    }

    red = vector<bool>(n, false);
    for(auto bound : sects) {
        vector<int> rec;
        for(int i = bound.first; i != bound.second; ++i) {
            if(i >= n) i -= n;
            if(i == bound.second) break;
            if(!red[i]) 
                rec.push_back(ns[i]);

            red[i] = true;
        }

        recursive(rec, out);
    }
    // cerr << "<\n";
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
        if(all_equal) {
            return 0;
            // cerr << "<\n";
        }
    }
    auto pr = convert(ns, s);
    int extra = get<1>(pr);
    ns = get<0>(pr);
    s = get<2>(pr);
    long long int sum_cycles = 0;
    for(int i = 0; i < ns.size(); ++i) {
        sum_cycles += (long long int) abs(ns[i] - i);
    }

    auto n = ns.size();
    auto uf = create_union_find(n);
    for(int i = 0; i < n; ++i) {
        join(i, ns[i], uf);
    }

    // rec_join_overlapped(0, n, uf);
    vector<int> colors;
    for(int i = 0; i < uf.size(); ++i) {
        colors.push_back(repr(i, uf));
        // cerr << colors.back() << endl;
    }

    // cerr << endl;

    // cout << "alive" << endl;
    recursive(colors, uf);


    for(int i = 0; i < n; ++i) {
        // cerr << repr(i, uf) << " ";
    }
    // cerr << endl;

    // cout << "alive" << endl;
    // cout << s << endl;
    int pat = extend(s, uf);

    // cout << "alive" << endl;
    // cout << pat << endl;

    return sum_cycles + (long long int)(extra * 2 + pat * 2);
}
