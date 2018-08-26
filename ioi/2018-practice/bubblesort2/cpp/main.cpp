#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

bool is_sorted(vector<ll> &ns) {
    for(int i = 0; i < int(ns.size())-1; ++i) if(ns[i] > ns[i+1]) return false;
    return true;
}

int quad(vector<ll> ns) {
    int k = 0;
    while(!is_sorted(ns)) {
        ++k;
        for(int i = 0; i < ns.size()-1; ++i) if(ns[i] > ns[i+1]) swap(ns[i], ns[i+1]);
    }
    return k;
}

int badd(vector<ll> ns) {
    int k = 0;
    for(int i = 0; i < ns.size(); ++i) {
        int count = 0;
        for(int j = 0; j < i; ++j) if(ns[j] > ns[i]) count++;
        k = max(k, count);
    }
    return k;
}

struct SegTree {
    int lo;
    int mid;
    int hi;
    SegTree *left;
    SegTree *right;

    int maximum; // Maximum of the values in each of its children;
    int lazy_delta;
};

SegTree* build(vector<int> &ns, int lo, int hi) {
    SegTree *s = new SegTree;
    s->lo = lo;
    s->hi = hi;
    s->lazy_delta = 0;

    if(ns->size() == 1) {
        s->mid = -1;
        s->left = nullptr;
        s->right = nullptr;
        s->maximum = ns[lo];
    } else {
        s->mid = (lo + hi) / 2;
        s->left = build(ns, s->lo, s->mid);
        s->right = build(ns, s->mid, s->hi);
        s->maximum = max(s->left->maximum, s->right->maximum)
    }
    return s;
}

void push(SegTree* s) {
    s->maximum += s->lazy_delta;

    s->left->lazy_delta += s->lazy_delta;
    s->right->lazy_delta += s->lazy_delta;

    s->lazy_delta = 0;
}

void apply(SegTree* s, int index, int delta) {
    push(s);
    if(index > s->hi) {
        s->lazy_delta += delta;
        push(s);
    } else {
        apply(s->left, index, delta);
        apply(s->right, index, delta);
    }
}

int main() {
    vector<ll> ns;
    for(int i = 0; i < 10000; ++i) ns.push_back(rand());
    int a = quad(ns);
    int b = badd(ns);

    cout << a << " " << b << endl;
}
