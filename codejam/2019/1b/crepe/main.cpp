#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    for(int test = 0; test < t; ++test) {
        int n, q;
        cin >> n >> q;
        // vector<pair<pair<int, int>, int>> ns(n);
        vector<pair<int, int>> ns[2];
        int total[2] = {0, 0};
        for(int i = 0; i < n; ++i) {
            int x, y;
            string c;
            cin >> x >> y >> c;

            int index = 1;
            if(c == "N" || c == "S") index = 0;

            int val = 1;
            if(c == "S" || c == "W") val = -1;
            else total[index]++;

            int tmp[2] = {y, x};
            ns[index].emplace_back(tmp[index], val);
        }
        int best[2] = {-1, -1};
        int ata[2] = {0xbeef, 0xc0ffee};
        for(int i = 0; i < 2; ++i) {
            sort(ns[i].begin(), ns[i].end());
            reverse(ns[i].begin(), ns[i].end());
            for(int j = 0; j <= q + 10; ++j) {
                while(!ns[i].empty() && ns[i].back() <= make_pair(j, -1)) {
                    total[i] += ns[i].back().second;
                    ns[i].pop_back();
                }
                if(total[i] > best[i]) {
                    best[i] = total[i];
                    ata[i] = j;
                }
                while(!ns[i].empty() && ns[i].back() <= make_pair(j, 1)) {
                    total[i] += ns[i].back().second;
                    ns[i].pop_back();
                }
            }
        }

        cout << "Case #" << test + 1 << ": " << ata[1] << " " << ata[0] << endl;
    }
}
