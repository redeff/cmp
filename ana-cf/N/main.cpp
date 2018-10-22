#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int total = 0;
    for(int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        bool is = true;
        unordered_set<int> lala;
        for(char c : s) lala.insert(c - '0');

        for(int i = 0; i <= k; ++i) if(lala.count(i) == 0) is = false;

        if(is) total++;
    }

    cout << total << endl;
}
