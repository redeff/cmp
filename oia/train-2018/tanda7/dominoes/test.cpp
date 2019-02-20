#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
    int n = rand() % (200000 - 2) + 2;
    int m = rand() % (200000 - 2) + 2;

    ofstream fout("2.in");
    fout << n << endl;
    for(int i = 0; i < n; ++i) {
        ll p = rand() % 1000000000;
        ll l = rand() % 1000000000 + 1;
        fout << p << " " << l << endl;
    }

    fout << m << endl;
    for(int i = 0; i < n; ++i) {
        int b = rand() % (n - 1) + 1;
        int a = rand() % b;
        fout << a + 1 << " " << b + 1 << endl;
    }
}
