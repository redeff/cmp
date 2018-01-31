#include <bits/stdc++.h>
using namespace std;

const int INF = 33333333;

#define ifs cin
#define ofs cout

int main() {
    ifstream ifs("maxinum.in");
    ofstream ofs("maxinum.out");
    int n;
    cin >> n;
    vector<int> ns(n);
    for(int i = 0; i < n; ++i) {
        cin >> ns[i];
    }

    struct Dp {
        int sum_of_pairs;
        int sum_of_other;
        Dp(int a, int b): sum_of_pairs(a), sum_of_other(b) {}
        Dp max(Dp a) {
            if(sum_of_pairs > a.sum_of_pairs) {
                return *this;
            } else {
                return a;
            }
        }
    };

    // dp[n] = main(ns[0:n+1])
    vector<Dp> dp(n + 1, Dp(-1, -1));
    // dp[0] = Dp(0, ns[0]);
    dp[0] = Dp(0, 0);
    for(int i = 1; i <= n; ++i) {
        // -------_
        Dp case_1 = dp[i - 1];
        case_1.sum_of_other += ns[i - 1];
        
        // ------#_#
        Dp case_2 = Dp(-INF, -INF);
        if(i >= 3) {
            case_2 = dp[i - 3];
            case_2.sum_of_other += ns[i - 2];
            case_2.sum_of_pairs += ns[i - 1] * ns[i - 3];
        }

        // -----@#@#
        Dp case_3 = Dp(-INF, -INF);
        if(i >= 4) {
            case_3 = dp[i - 4];
            case_3.sum_of_pairs += ns[i - 1] * ns[i - 3];
            case_3.sum_of_pairs += ns[i - 4] * ns[i - 2];
        }

        dp[i] = case_1.max(case_2.max(case_3));
    }

    cout << dp[n].sum_of_pairs << endl;
    cout << dp[n].sum_of_other << endl;
}
