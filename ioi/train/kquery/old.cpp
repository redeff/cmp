#include <bits/stdc++.h>
using namespace std;
 
const int INF = 1003333333;
 
int lg(int n) {
    int out = 1;
    while(out < n) out *= 2;
    return out;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    
    vector<vector<int>> ns;
    int l = lg(n);
    ns.emplace_back(l, 0);
    for(int i = 0; i < n; ++i) {
        cin >> ns.back()[i];
    }
 
    n = l;
 
    int p = 2;
    while(p <= n) {
        ns.emplace_back(n, -1);
        for(int i = 0; i < n; i += p) {
            int a = i;
            int b = i + (p / 2);
            for(int j = 0; j < p; ++j) {
                if((a == i + (p/2) ? INF : ns[ns.size() - 2][a]) < (b == i + p ? INF : ns[ns.size() - 2][b])) {
                    ns.back()[i + j] = ns[ns.size() - 2][a];
                    a++;
                } else {
                    ns.back()[i + j] = ns[ns.size() - 2][b];
                    b++;
                }
            }
        }
        p = p << 1;
    }
 
    function<int (int, int)> sum_suffix = [&](int s, int k) {
        if(s == n) return 0;
        int level = 0;
        while(s % (1 << level) == 0 && 1 << level <= n) level++;
        level--;
 
        auto b = ns[level].begin() + s;
        auto e = ns[level].begin() + s + (1 << level);
 
        auto it = upper_bound(b, e, k);
        int total = (1 << level) - distance(b, it);
 
        return total + sum_suffix(s + (1 << level), k);
    };
 
    // cout << sum_suffix(5, 3) << endl;
 
    /*
    for(auto &v : ns) {
        for(auto i : v) {
            cout << i << " ";
        } cout << endl;
    }
    */
 
    int q;
    cin >> q;
    for(int lala = 0; lala < q; ++lala) {
        int a, b, k;
        cin >> a >> b >> k;
        cout << sum_suffix(a - 1, k) - sum_suffix(b, k) << "\n";
    }
}
