#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll MOD

struct Uf {
    Uf *dad;
    int deg;
    ll ways;
};

Uf *repr(Uf *a) {
    while(a->dad != a) {
        a->dad = a->dad->dad;
        a = a->dad;
    }
    return a;
}

void join(Uf *a, Uf *b) {
    a = repr(a);
    b = repr(b);
    if(a->deg < b->deg) swap(a, b);
    if(a->deg == b->deg) a->deg++;
    a->ways *= b->ways;
    a->ways %= MOD;
    b->dad = a;
}