#include "bubblesort2.h"
#include <bits/stdc++.h>
using namespace std;

#define ALL(x) x.begin(), x.end()

typedef long long int ll;

struct SegTree {
    int hi;
    int lo;
    SegTree *left;
    SegTree *right;

    int maximum; // Maximum of the values in each of its children;
    int lazy_delta;
};

SegTree* build(vector<int> &ns, int lo, int hi) {
    SegTree *s = new SegTree;
    s->hi = hi;
    s->lo = lo;
    s->lazy_delta = 0;

    if(hi - lo == 1) {
        s->left = nullptr;
        s->right = nullptr;
        s->maximum = ns[lo];
    } else {
        int mid = (lo + hi) / 2;
        s->left = build(ns, lo, mid);
        s->right = build(ns, mid, hi);
        s->maximum = max(s->left->maximum, s->right->maximum);
    }
    return s;
}

void push(SegTree* s) {
    s->maximum += s->lazy_delta;

    if(s->left != nullptr) {
        s->left->lazy_delta += s->lazy_delta;
        s->right->lazy_delta += s->lazy_delta;
    }

    s->lazy_delta = 0;
}

void apply(SegTree* s, int index, int delta) {
    push(s);
    if(index >= s->hi) {
        s->lazy_delta += delta;
        push(s);
    } else if(s->lo >= index) return;
    else {
        apply(s->left, index, delta);
        apply(s->right, index, delta);
        s->maximum = max(s->left->maximum, s->right->maximum);
    }
}

void point(SegTree* s, int index, int delta) {
    apply(s, index + 1, delta);
    apply(s, index, -delta);
}

std::vector<int> count_scans(std::vector<int> origs, std::vector<int> poss, std::vector<int> vals) {
    int n = origs.size();
    vector<int> compressed = origs;
    for(auto v : vals) compressed.push_back(v);

    sort(ALL(compressed));
    compressed.erase(unique(compressed.begin(), compressed.end()), compressed.end());

    for(int &o : origs) o = lower_bound(ALL(compressed), o) - compressed.begin();
    for(int &o : vals) o = lower_bound(ALL(compressed), o) - compressed.begin();

    int k = compressed.size();

    vector<set<int>> indexes(k);
    for(int i = 0; i < n; ++i) indexes[origs[i]].insert(i); 

    vector<int> partials(k);
    for(int i = k-1; i > 0; --i) partials[i-1] = partials[i] + indexes[i].size();

    for(int i = 0; i < k; ++i) if(!indexes[i].empty()) partials[i] += *indexes[i].rbegin();

    SegTree *s = build(partials, 0, partials.size());

    vector<int> answer(poss.size());
    for(int q = 0; q < poss.size(); ++q) {
        int pos = poss[q];
        int from = origs[pos];
        int to = vals[q];

        origs[pos] = to;

        apply(s, from, -1);
        apply(s, to, 1);

        point(s, from, -*indexes[from].rbegin());
        indexes[from].erase(pos);
        if(!indexes[from].empty())
            point(s, from, *indexes[from].rbegin());

        if(!indexes[to].empty())
            point(s, to, -*indexes[to].rbegin());
        indexes[to].insert(pos);
        point(s, to, *indexes[to].rbegin());

        answer[q] = s->maximum - n + 1;
    }

    return answer;
}
