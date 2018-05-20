#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll calc(ll b, ll c) {
    if(2 * b == c) return 0;
    if(c % 2 == 1) return 1ll + min(calc(b, c + 1), calc(b, c - 1));
    return abs(b - c) / 2;
}

void doit() {
    ll a, b, c;
    cin >> a >> b >> c;

    cout << calc(b - a, c - a) << endl;
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) doit();
}
