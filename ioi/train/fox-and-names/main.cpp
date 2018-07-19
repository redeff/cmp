#include <bits/stdc++.h>
using namespace std;

const int letters = 26;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<string> words(n);
    for(int i = 0; i < n; ++i) cin >> words[i];

    vector<vector<int>> dag(letters);
    vector<int> indegree(letters, 0);
    for(int i = 1; i < n; ++i) {
        int k = 0;
        int bound = min(words[i - 1].size(), words[i].size());
        while(k < bound && words[i - 1][k] == words[i][k]) k++;
        if(k == bound) {
            if(words[i - 1].size() > words[i].size()) {
                cout << "Impossible\n";
                return 0;
            }
        } else {
            dag[words[i - 1][k] - 'a'].push_back(words[i][k] - 'a');
            indegree[words[i][k] - 'a']++;
        }
    }

    vector<int> topo;
    vector<int> blob;
    for(int i = 0; i < letters; ++i) {
        if(indegree[i] == 0) blob.push_back(i);
    }

    while(!blob.empty()) {
        int t = blob.back();
        blob.pop_back();
        topo.push_back(t);

        for(int ch : dag[t]) {
            if(--indegree[ch] == 0) blob.push_back(ch);
        }
    }

    if(topo.size() != letters) cout << "Impossible\n";
    else {
        for(int i : topo) cout << (char)(i + 'a');
        cout << endl;
    }
}
