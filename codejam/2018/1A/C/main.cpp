#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

void testcase() {
    int n;
    double p;
    cin >> n >> p;

    vector<double> ws(n);
    vector<double> hs(n);

    for(int i = 0; i < n; ++i) {
        cin >> ws[i] >> hs[i];
    }

    vector<double> mn(n);
    vector<double> mx(n);

    double per = 0;

    for(int i = 0; i < n; ++i) {
        mn[i] = 2.0 * min(ws[i], hs[i]);
        mx[i] = 2.0 * sqrt(ws[i] * ws[i] + hs[i] * hs[i]);
        per += 2.0 * (ws[i] + hs[i]);
    }

    vector<pair<double, double>> rs = {{0.0, 0.0}};
    for(int i = 0; i < n; ++i) {
        vector<pair<double, double>> nrs;
        for(auto r : rs) {
            nrs.push_back(r);
            nrs.emplace_back(r.first + mn[i], r.second + mx[i]);
        }

        sort(nrs.begin(), nrs.end(), [&](pair<double, double> a, pair<double, double> b) {return a.first < b.first;});

        rs = {};
        
        for(int j = 0; j < nrs.size();) {
            double nd = nrs[j].second;
            double st = nrs[j].first;
            while(j < nrs.size() && nrs[j].first <= nd) {
                nd = max(nd, nrs[j].second);
                j++;
            }

            rs.emplace_back(st, nd);
        }
    }

    double diff = 3333333333333;
    for(pair<double, double> r : rs) {
        if(r.first + per > p) continue;
        else diff = min(diff, max(0.0, p - (r.second + per))); 
    }

    cout << setprecision(17);
    cout << p - diff << endl;
}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cout << "Case #" << i + 1 << ": ";
        testcase();
    }
}
