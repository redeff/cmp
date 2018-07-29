#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        ll n, a, b;
        cin >> n >> a >> b;

        auto fun = [&](ll x) {
            return a * x * x + b * (n - x) * (n - x);
        };

        auto grow = [&](ll x) {
            return fun(x + 1) - fun(x);
        };

        ll lo = 0;
        ll hi = n;
        while(hi - lo > 1) {
            ll mid = (hi + lo) / 2;
            if(grow(mid) < 0) lo = mid;
            else hi = mid;
        }

        cout << min(fun(lo), fun(hi)) << endl;

        // Minimize ax^2 + b(n - x)^2 =
        // ax^2 + bn^2 + bx^2 - 2nx => derive
        // 2ax + 0 + 2bx - 2n = 0
        // ax + bx = n
        // x(a + b) = n
        // x = n / (a + b)
        /*

        int x1 = n / (a + b);
        int x2 = x1 + 1;

        x1 = min(x1, n);
        x1 = max(0, x1);

        x2 = min(x2, n);
        x2 = max(0, x2);

        cout << min(fun(n, a, b, x1), fun(n, a, b, x2)) << endl;
        */

    }
}
