#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

void testcase() {
    int r, c, h, v;
    cin >> r >> c >> h >> v;
    vector<vector<bool>> ns(c, vector<bool>(r));

    int chips = 0;
    vector<int> by_col(c, 0);
    vector<int> by_row(r, 0);
    for(int y = 0; y < r; ++y) {
        for(int x = 0; x < c; ++x) {
            char c;
            cin >> c;
            ns[x][y] = c == '@';
            if(ns[x][y]) {
                chips++;
                by_col[x]++;
                by_row[y]++;
            }
        }
    }

    if(chips == 0) {cout << "POSSIBLE" << endl; return; }

    int cust = (h + 1) * (v + 1);
    if(chips % cust == 0) {
        int each = chips / cust;

        int sm = 0;
        int last = 0;
        // TODO: check v or h 0
        vector<int> xs {-1};
        for(int x = 0; x < c; ++x) {
            sm += by_col[x];
            // if(sm % (each * (h + 1)) == 0 && (x == 0 || by_col[x] != 0)) xs.push_back(x);
            if(sm == last + each * (h + 1)) {
                last = last + each * (h + 1);
                xs.push_back(x);
            }
        }

        sm = 0;
        last = 0;
        vector<int> ys {-1};
        for(int y = 0; y < r; ++y) {
            sm += by_row[y];
            // if(sm % (each * (v + 1)) == 0 && (y == 0 || by_col[y] != 0)) ys.push_back(y);
            if(sm == last + each * (v + 1)) {
                last = last + each * (v + 1);
                ys.push_back(y);
            }
        }

        if(xs.size() != v + 2 || ys.size() != h + 2) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }

        /*
        for(int x : xs) cerr << x << " ";
        cerr << endl;

        for(int y : ys) cerr << y << " ";
        cerr << endl;
        */

        for(int x = 1; x < xs.size(); ++x) {
            for(int y = 1; y < ys.size(); ++y) {
                int total = 0;
                for(int x1 = xs[x - 1] + 1; x1 <= xs[x]; ++x1) {
                    for(int y1 = ys[y - 1] + 1; y1 <= ys[y]; ++y1) {
                        if(ns[x1][y1]) total++;
                    }
                }

                if(total != each) {
                    cout << "IMPOSSIBLE" << endl;
                    return;
                }
            }
        }

    } else {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    cout << "POSSIBLE" << endl;

}

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cout << "Case #" << i + 1 << ": ";
        testcase();
    }
}
