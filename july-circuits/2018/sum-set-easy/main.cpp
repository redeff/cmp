#include <bits/stdc++.h>
using namespace std;

int main() {
    unordered_set<int> as;
    {
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            int tmp;
            cin >> tmp;
            as.insert(tmp);
        }
    }

    unordered_set<int> cs;
    {
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            int tmp;
            cin >> tmp;
            cs.insert(tmp);
        }
    }

    for(int b = 1; b <= 100; ++b) {
        bool god = true;
        for(int a : as) if(cs.count(a + b) == 0) god = false;
        if(god) cout << b << " ";
    }
    cout << endl;
}
