#include <bits/stdc++.h>
using namespace std;

#define ALL(x) x.begin(), x.end()

int main() {
    int n = 5000;
    cout << n << endl;
    vector<int> ns(n);
    for(int i = 0; i < n; ++i) {
        ns[i] = i;
    }
    random_shuffle(ALL(ns));
    if(min_element(ALL(ns)) > max_element(ALL(ns))) reverse(ALL(ns));
    for(int i : ns) cout << i << endl;
}
