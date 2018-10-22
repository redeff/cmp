#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if(a < b) swap(a, b);
    if(b == 0) return a;
    return gcd(b, a%b);
}

int main() {
    int n;
    cin >> n;
    vector<int> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i];
    int k = ns[0];
    for(int i = 1; i < n; ++i) k = gcd(k, ns[i]);
    cout << k*n << endl;
}
