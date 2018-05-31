#include <vector>

using namespace std;
const int INF = 333333333;

vector<int> electromovil(int n, vector<int> start, vector<int> len) {
    len[n - 1] = INF;
    vector<int> end(n);
    for(int i = 0; i < n; ++i) {
        end[i] = start[i] + len[i];
    }

    vector<int> pat;
    pat.push_back(0);
    while(true) {
        int best = pat.back();
        int curr = pat.back();
        for(int i = curr; i < n && start[i] <= end[curr]; ++i) {
            if(end[i] > end[best]) best = i;
        }
        if(best == curr) break;
        pat.push_back(best);
    }
    pat.erase(pat.begin());
    if(pat.back() != n - 1) return {};
    else {
        for(int i = 0; i < pat.size(); ++i) pat[i] = start[pat[i]];
        return pat;
    }
}
