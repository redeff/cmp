#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for(; t; --t) {
        int n;
        cin >> n;
        vector<int> letters(26, false);
        vector<int> cols(26);
        vector<bool> seen(26, false);
        for(int i = 0; i < 26; ++i) cols[i] = i;

        int total = 0;
        int merg = 0;
        int num = 0;
        for(int i = 0; i < n; ++i) {
            string word;
            cin >> word;
            int fst = word.front() - 'a';
            int lst = word.back() - 'a';
            letters[fst]++;
            if(letters[fst] == 0) total--;
            else total++;

            letters[lst]--;
            if(letters[lst] == 0) total--;
            else total++;

            if(!seen[fst]) {
                seen[fst] = true;
                num++;
            }
            if(!seen[lst]) {
                seen[lst] = true;
                num++;
            }

            if(cols[fst] != cols[lst]) {
                merg++;
                int c = cols[lst];
                for(int i = 0; i < 26; ++i)
                    if(cols[i] == c) cols[i] = cols[fst];
            }
        }
        cout << (total <= 2 && merg == num - 1 ? "Ordering is possible.\n" : "The door cannot be opened.\n");
    }
}
