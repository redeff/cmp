#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

void doit() {
    ll x;
    cin >> x;
    ll stat = 1;

    while(stat * (stat + 1) / 2 < x) stat++;

    ll res = min(stat * (stat + 1) / 2 - x + stat, x - (stat * (stat - 1)) / 2 + stat - 1);
    cout << res << endl;
}

int main() {
    ll t;
    cin >> t;
    for(int i = 0; i < t; ++i) doit();
}
