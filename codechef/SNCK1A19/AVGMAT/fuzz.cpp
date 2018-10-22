#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 300;
    int m = 300;
    cout << 1 << endl;
    cout << n << " " << m << endl;
    for(int x = 0; x < n; ++x) {
        for(int y = 0; y < m; ++y) {
            if(rand() % 2 == 0) cout << '1';
            else cout << '0';
        }
        cout << endl;
    }
}
