#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 333333333;


void doit() {
    int n;
    cin >> n;

    int mx_a = -INF;
    int sm_a = 0;

    for(int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        mx_a = max(mx_a, t);
        sm_a += t;
    }

    int mx_b = -INF;
    int sm_b = 0;

    for(int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        mx_b = max(mx_b, t);
        sm_b += t;
    }

    sm_b -= mx_b;
    sm_a -= mx_a;

    if(sm_a < sm_b) {
        cout << "Alice" << endl;
    } else if(sm_a > sm_b) {
        cout << "Bob" << endl;
    } else {
        cout << "Draw" << endl;
    }
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) doit();
}
