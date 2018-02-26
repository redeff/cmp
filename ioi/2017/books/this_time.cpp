#include <bits/stdc++.h>
using namespace std;

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

void recursive(vector<int> ns, vector<pair<int, int>> &out) {
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
                    out.emplace_back(*it, *next(it));
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
                                out.emplace_back(color, *colors.begin());
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

int main() {
    // vector<int> rec = {1000, 40, 1000, 40, 50, 50, 40, 50};
    // vector<int> rec = {10, 20, 0, 10, 20};
    // vector<int> rec = {10, 10, 10, 10, 10, 101};
    // vector<int> rec = {10, 20, 30, 30, 20, 10};
    // vector<int> rec = {1, 1, 2, 2};
    // vector<int> rec = {1, 1};
    // vector<int> rec = {1, 1, 1, 1, };
    // vector<int> rec = {10, 10, 0, 0, 10, 15, 15, 0, 10, 8, 8, 15};
    // vector<int> rec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
    // vector<int> rec = {3, 0, 1, 1, 1, 2, 1, 0, 0, 0,  3,  3,  0,  4,  5,  5,  5,  4};
    // vector<int> rec = {10, 1000, 1000, 1000, 10};
    vector<int> rec = {1, 1, 1, 1};
    vector<pair<int, int>> result;
    recursive(rec, result);

    for(auto p : result) cout << p.first << " " << p.second << endl;
}
