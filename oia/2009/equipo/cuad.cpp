#include <bits/stdc++.h>
using namespace std;

/*
#define cin ifs
#define cout ofs
*/

string eq_prefix(string a, string b) {
    string total = "";
    for(int i = 0; i < a.size(); ++i) {
        if(a[i] == b[i]) total.push_back(a[i]);
        else break;
    }

    return total;
}

int main() {
    // ifstream ifs("equipo.in");
    // ofstream ofs("equipo.out");
    int p, c;
    cin >> p >> c;
    vector<string> s(c);
    for(int i = 0; i < c; ++i) {
        cin >> s[i];
    }

    sort(s.begin(), s.end());
    string best_str;
    int best = 0;

    for(int i = 0; i < c; ++i) {
        for(int j = i + 1; j < c; ++j) {
            string pr = eq_prefix(s[i], s[j]);
            int ad = pr.size() * pr.size() * (j + 1 - i);

            if(best < ad) {
                best = ad;
                best_str = pr;
            }
        }
    }

    cout << best << endl;
    cout << best_str << endl;
}
