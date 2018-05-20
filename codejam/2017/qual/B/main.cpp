#include <bits/stdc++.h>
using namespace std;

vector<int> doit(vector<int> ns) {
    int n = ns.size();

    int first_decrease = -1;
    for(int i = 0; i < n - 1; ++i) {
        if(ns[i] > ns[i + 1]) {
            first_decrease = i;
            break;
        }
    }

    if(first_decrease != -1) {
        while(first_decrease != 0 && ns[first_decrease] == ns[first_decrease - 1]) first_decrease--;
        ns[first_decrease]--;
        for(int i = first_decrease + 1; i < n; ++i) {
            ns[i] = 9;
        }
    }
    if(ns[0] == 0) ns.erase(ns.begin());
    return ns;
}

void testcase() {
    string n;
    cin >> n;
    vector<int> ns;
    for(char c : n) ns.push_back(c - '0');

    auto res = doit(ns);
    for(int r : res) cout << r;
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cout << "Case #" << i + 1 << ": ";
        testcase();
    }
}
