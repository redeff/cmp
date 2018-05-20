#include <bits/stdc++.h>
using namespace std;

// Afinidad, indices, depth
pair<int, pair<pair<int, int>, int>> rec(int depth, int lo, int hi, vector<string> &s) {
    // cerr << depth << " " << lo << " " << hi << endl;
    if(lo == hi || lo + 1 == hi) return {-1, {{-1, -1}, -1}};
    pair<int, pair<pair<int, int>, int>> best = {(hi - lo) * depth * depth, {{lo, hi}, depth}};
    if(depth < int(s.back().size())) {
        int prv = lo;
        for(int i = lo + 1; i <= hi; ++i) {
            if(i == hi || s[i][depth] != s[i - 1][depth]) {
                auto nbest = rec(depth + 1, prv, i, s);
                if(nbest.first > best.first) best = nbest;
                prv = i;
            }
        }
    }

    return best;
}

#define cin ifs
#define cout ofs

int main() {
    ifstream ifs("equipo.in");
    ofstream ofs("equipo.out");
    int p, c;
    cin >> p >> c;
    vector<string> s(c);
    for(int i = 0; i < c; ++i) {
        cin >> s[i];
    }

    sort(s.begin(), s.end());
    auto best = rec(0, 0, c, s);
    cout << best.first << endl;
    for(int i = 0; i < best.second.second; ++i) {
        cout << s[best.second.first.first][i];
    } cout << endl;
}
