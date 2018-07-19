#include <bits/stdc++.h>
using namespace std;

const double e = 1e-8;
const double INF = 1e8;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for(int testcase = 1; true; ++testcase) {
        int n;
        cin >> n;
        if(n == 0) break;
        vector<string> words(n);
        for(int i = 0; i < n; ++i) cin >> words[i];

        sort(words.begin(), words.end());

        int m;
        cin >> m;
        vector<vector<double>> graph(n, vector<double>(n, INF)); 
        for(int i = 0; i < m; ++i) {
            string wa, wb;
            double wei;
            cin >> wa >> wei >> wb;
            int a = lower_bound(words.begin(), words.end(), wa) - words.begin();
            int b = lower_bound(words.begin(), words.end(), wb) - words.begin();

            // graph[a].push_b0ack({b, 1.0 / wei});
            graph[a][b] = 1.0 / wei;
            // graph[b].push_back({a, 1.0 / wei});
        }

        for(int i = 0; i < n; ++i) {
            for(int a = 0; a < n; ++a) {
                for(int b = 0; b < n; ++b) {
                    graph[a][b] = min(graph[a][b], graph[a][i] * graph[i][b]);
                }
            }
        }

        bool pos = false;
        for(int i = 0; i < n; ++i) {
            if(graph[i][i] < 1 - e) {
                pos = true;
            }
        }
        cout << "Case " << testcase << ": " << (pos ? "Yes" : "No") << endl;
    }
}
