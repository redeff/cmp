#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<vector<int>> letters('z' - 'a');
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); ++i) {
        letters[s[i] - 'a'].push_back(i);
    }
    double total = 0;
    for(int i = 0; i < letters.size(); ++i) {
        if(letters[i].size() == 0) continue;
        double prob = 0;
        for(int j = 0; j < s.size(); ++j) {
            vector<int> num_used('z' - 'a', 0);
            for(int l : letters[i]) {
                num_used[s[(l + j) % s.size()] - 'a']++;
            }

            int used = 0;
            for(int k = 0; k < num_used.size(); ++k) {
                if(num_used[k] != 0) used++;
            }

            cout << used << endl;
            prob = max(prob, (double)used / (double)letters[i].size());
        }

        total += prob * double(letters[i].size()) / double(s.size());
        cout << char(i + 'a') << " " << total << endl;
    }

    cout << total << endl;
}
