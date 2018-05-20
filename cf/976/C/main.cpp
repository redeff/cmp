#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
    int n;
    cin >> n;

    struct Segment {
        ll start;
        ll end;

        bool operator==(Segment s) {
            return start == s.start && end == s.end;
        }
    };

    vector<Segment> ns(n);
    for(int i = 0; i < n; ++i) {
        ll start, end;
        cin >> start >> end;
        ns[i].start = start;
        ns[i].end = end;
    }

    vector<int> by_start(n);
    vector<int> by_end(n);

    for(int i = 0; i < n; ++i) {
        by_start[i] = i;
        by_end[i] = i;
    }

    sort(by_start.begin(), by_start.end(), [&](int a, int b) {
            if(ns[a].start < ns[b].start) return true;
            if(ns[a].start > ns[b].start) return false;
            if(ns[a].end > ns[b].end) return true;
            if(ns[a].end < ns[b].end) return false;
            if(a < b) return true;
            if(a > b) return false;
            return false;
            });

    sort(by_end.begin(), by_end.end(), [&](int a, int b) {
            if(ns[a].end < ns[b].end) return true;
            if(ns[a].end > ns[b].end) return false;
            if(ns[a].start > ns[b].start) return true;
            if(ns[a].start < ns[b].start) return false;
            if(a > b) return true;
            if(a < b) return false;
            return false;
            });

    for(int i = 0; i < n; ++i) {
        if(by_end[i] != by_start[i]) {
            cout << 1 + by_end[i] << " " << 1 + by_start[i] << endl;
            return 0;
        }
    }

    cout << -1 << " " << -1 << endl;

}
