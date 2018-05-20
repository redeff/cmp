#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node *nxt;
    Node *prv;

    Node *nxt_cyc;
    Node *prv_cyc;

    int index;
};

struct Range {
    Node* b;
    Node* e;

    Range(Node* b, Node* e): b(b), e(e) {}
    Range() {}

    bool contains(Node* i) {
        if(b->index <= e->index) return b->index <= i->index && i->index <= e->index;
        else return i->index <= e->index || b->index <= i->index;
    }
};

void set_cyc(Node* a, Node* b) {
    a->nxt_cyc = b;
    b->prv_cyc = a;
}

void fuse(Node *a, Node *b) {
    if(a == b) return;
    if(a == a->nxt_cyc && b == b->nxt_cyc) {
        set_cyc(a, b);
        set_cyc(b, a);
        return;
    }

    if(a == a->nxt_cyc) {
        set_cyc(a, b->nxt_cyc);
        set_cyc(b, a);
        return;
    } else if(b == b->nxt_cyc) {
        set_cyc(b, a->nxt_cyc);
        set_cyc(a, b);
        return;
    }

    Range as(a, a->nxt_cyc);

    Node* bs[4];
    bs[0] = b;
    for(int i = 1; i < 4; ++i) {
        bs[i] = bs[i - 1]->nxt_cyc;
    }

    for(int i = 0; i < 4; ++i) {
        if(bs[i] == as.b || bs[i] == as.e) return;
    }

    for(int i = 1; i < 4; ++i) {
        if(as.contains(bs[i - 1]) != as.contains(bs[i])) return;
    }

    for(int i = 1; i < 4; ++i) {
        if(as.contains(bs[i]) != Range(bs[i - 1], bs[i]).contains(as.b)) {
            set_cyc(as.b, bs[i]);
            set_cyc(bs[i - 1], as.e);
            return;
        }
    }

    // Don't ask
    set_cyc(bs[0], bs[2]);
    set_cyc(bs[2], as.e);

    set_cyc(as.b, bs[1]);
    set_cyc(bs[1], bs[3]);
}

void doit(Node *start) {
    if(start->nxt == start) return;
    if(start->nxt_cyc == start) {
        Node *prv = start->prv;
        Node *nxt = start->nxt;

        prv->nxt = nxt;
        nxt->prv = prv;
        doit(nxt);

        prv->nxt = start;
        nxt->prv = start;
        return;
    }

    int n = start->prv->index - start->index;

    auto cmp_len = [&](Range a, Range b) {
        Node* ap = a.b;
        Node* bp = b.b;

        while(ap != a.e && bp != b.e) {
            ap = ap->nxt;
            bp = bp->nxt;
        }

        return ap == a.e;
    };

    auto len = [&](Range r) {
        int ix_b = r.b->index;
        int ix_e = r.e->index;
        if(ix_b < ix_e) return ix_e - ix_b;
        else return n - (ix_b - ix_e);
    };

    Range big(start, start->nxt_cyc->prv), sml(start->nxt_cyc, start->prv);
    if(cmp_len(big, sml)) {
        Range tmp = big;
        big = sml;
        sml = tmp;
    }
    vector<Node*> big_cyc;
    vector<Node*> sml_cyc;

    for(Node* i = sml.b; i != sml.e->nxt; i = i->nxt) {
        if(big.contains(i->prv_cyc)) {
            big_cyc.push_back(i->prv_cyc);
            sml_cyc.push_back(i);

            Node* go_back = i;
            while(sml.contains(go_back->nxt_cyc)) {
                go_back = go_back->nxt_cyc;
            }

            set_cyc(i->prv_cyc, go_back->nxt_cyc);
            set_cyc(go_back, i);
        }
    }

    for(int i = 1; i < big_cyc.size(); ++i) {
        /*
        cerr << "index " << big_cyc[i - 1]->index << endl;
        cerr << "index " << big_cyc[i]->index << endl;
        */
        fuse(big_cyc[i - 1], big_cyc[i]);
    }

    for(int i = 1; i < sml_cyc.size(); ++i) {
        fuse(sml_cyc[i - 1], sml_cyc[i]);
    }

    big.e->nxt = big.b;
    big.b->prv = big.e;

    sml.e->nxt = sml.b;
    sml.b->prv = sml.e;

    doit(sml.b);
    doit(big.b);

    
    big.e->nxt = sml.b;
    big.b->prv = sml.e;

    sml.e->nxt = big.b;
    sml.b->prv = big.e;

    Node* nxt_big = big.b->nxt_cyc;
    Node* nxt_sml = sml.b->nxt_cyc;

    set_cyc(big.b, nxt_sml);
    set_cyc(sml.b, nxt_big);

}

long long int minimum_walk(vector<int> nexts, int start) {
    int n = nexts.size();

    vector<Node> ns(n);

    for(int i = 0; i < n; ++i) {
        int t = nexts[i];
        ns[i].nxt_cyc = &ns[t];
        ns[t].prv_cyc = &ns[i];
        ns[i].index = i;
    }

    for(int i = 1; i < n; ++i) {
        ns[i].prv = &ns[i - 1];
        ns[i - 1].nxt = &ns[i];
    }
    ns[n-1].nxt = &ns[0];
    ns[0].prv = &ns[n-1];

    doit(&ns[0]);
    int c = 0;

    struct Rng {
        int mn;
        int mx;
    };

    vector<Rng> colors;
    vector<int> color(n, -1);
    for(int i = 0; i < n; ++i) {
        if(color[i] == -1) {
            colors.emplace_back();
            colors.back().mn = i;
            colors.back().mx = i;
            color[i] = c;
            for(int j = ns[i].nxt_cyc - &ns[0]; j != i; j = ns[j].nxt_cyc - &ns[0]) {
                color[j] = c;
                if(j < colors.back().mn) colors.back().mn = j;
                if(j > colors.back().mx) colors.back().mx = j;
            }
            ++c;
        }
    }
    int lob = 0;
    int hib = n - 1;
    while(lob < n && ns[lob].nxt_cyc == &ns[lob]) ++lob;
    if(lob == n) return 0;
    while(ns[hib].nxt_cyc == &ns[hib]) --hib;

    int lo = colors[color[start]].mn;
    int hi = colors[color[start]].mx;
    int total = 0;
    int since_last = 0;
    while(true) {
        if(lo <= lob && hi >= hib) break;
        if(lo > lob) lo--, total++;
        if(hi < hib) hi++, total++;
        since_last++;
        lo = colors[color[lo]].mn;
        hi = colors[color[hi]].mx;
        if(colors[color[hi]].mn <= lo) {
            lo = colors[color[hi]].mn; 
            total -= since_last;
            since_last = 0;
        }

        if(colors[color[lo]].mx >= hi) {
            hi = colors[color[lo]].mx; 
            total -= since_last;
            since_last = 0;
        }
    }

    long long int sum_cycles = 0;

    for(int i = 0; i < n; ++i) {
        sum_cycles += (long long int) abs(i - nexts[i]);
    }
    return sum_cycles + 2 * (long long int) total;
}

