#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll INF = 3333333333333;

struct Rect {
    ll xlo;
    ll xhi;
    ll ylo;
    ll yhi;
    bool empty() {
        return xlo > xhi || ylo > yhi;
    }
    /*
    Rect() {
        xlo = -INF;
        xhi = INF;
        ylo = -INF;
        xhi = INF;
    }
    */
};

Rect zero() {
    return Rect {
        -INF,
        INF,
        -INF,
        INF
    };
}

Rect intersect(Rect a, Rect b) {
    return Rect {
        max(a.xlo, b.xlo),
        min(a.xhi, b.xhi),
        max(a.ylo, b.ylo),
        min(a.yhi, b.yhi)
    };
}

int main() {
    ll n;
    cin >> n;
    vector<Rect> ns(n); 
    for(int i = 0; i < n; ++i) {
        cin >> ns[i].xlo >> ns[i].ylo >> ns[i].xhi >> ns[i].yhi;
    }

    vector<Rect> par_left(n);
    par_left[0] = zero();
    for(int i = 1; i < n; ++i) {
        par_left[i] = intersect(par_left[i-1], ns[i-1]);
    }

    vector<Rect> par_right(n);
    par_right.back() = zero();
    for(int i = n - 2; i >= 0; --i) {
        par_right[i] = intersect(par_right[i+1], ns[i+1]);
    }

    for(int i = 0; i < n; ++i) {
        Rect r = intersect(par_right[i], par_left[i]);
        if(!r.empty()) {
            cout << r.xlo << " " << r.ylo << endl;
            return 0;
        }
    }
}
