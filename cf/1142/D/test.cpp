#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> ns;
    for(int i = 1; i <= 9; ++i) ns.push_back(i);
    int total = 20000;
    cin >> total;
    for(int i = 10; i < total; ++i) {
        auto it = lower_bound(ns.begin(), ns.end(), (int) (i/10));
        int k = it - ns.begin() + 1;
        if(*it == i / 10 && (i % 10) < (k % 11))
            ns.push_back(i);
    }
    int mod = 100;
    /*
    for(int i = 0; i < total; ++i) {
        auto it = lower_bound(ns.begin(), ns.end(), (int) (i));
        if(*it == i) cout << '#';
        else cout << ' ';
        if(i % mod == mod - 1) cout << endl;
    }
    */
    cout << ns.size() << endl;
    // for(int i : ns) cout << i << endl;
    // cout << endl;
}
