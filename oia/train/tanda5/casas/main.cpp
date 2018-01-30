#include <bits/stdc++.h>
using namespace std;

const int INF = 33333333;

// #define LOCAL

#ifndef LOCAL
#define ifs cin
#define ofs cout
#endif //LOCAL

int main() {
#ifndef LOCAL
    ifstream ifs("casas.in");
    ofstream ofs("casas.out");
#endif //LOCAL
    

    int x, y;
    cin >> x >> y;
    int c;
    cin >> c;

    vector<int> cs(c);
    for(int i = 0; i < c; ++i) {
        cin >> cs[i];
    }

    int size = x / 2;

    struct Entry {
        int area;
        int from;
        int size;
        Entry(int area_, int from_, int size_): area(area_), from(from_), size(size_) {}
        Entry(){}
    };

    vector<vector<Entry>> dp(c, vector<Entry>(size, Entry(-INF, -1, -1)));
    for(int i = 0; i < cs[0]; ++i) {
        int dist = cs[0] - i;
        if(dist <= size && dist + cs[0] <= y) {
            dp[0][dist - 1].area = dist * dist * 4; 
            dp[0][dist - 1].size = dist; 
        }
    }

    for(int i = 1; i < c; ++i) {
        int max_area = -INF;
        int from = -1;
        for(int j = cs[i - 1] + 1; j < cs[i]; ++j) {
            int dist_to_prev = j - cs[i - 1];
            int dist_to_next = cs[i] - j;
            if(dist_to_prev <= size) {
                int this_area = dp[i - 1][dist_to_prev - 1].area;
                if(this_area > max_area) {
                    max_area = this_area;
                    from = dist_to_prev - 1;
                }
                // max_area = max(max_area, dp[i - 1][dist_to_prev - 1].area);
            }

            if(dist_to_next <= size && cs[i] + dist_to_next <= y) {
                dp[i][dist_to_next - 1].area = max_area + 4 * dist_to_next * dist_to_next;
                dp[i][dist_to_next - 1].size = dist_to_next;
                dp[i][dist_to_next - 1].from = from;
            }
        }
    }

    Entry mx(-INF, -1, -1);
    for(int i = 0; i < size; ++i) {
        if(dp.back()[i].area > mx.area) {
            mx = dp.back()[i];
        }
    }

    cout << mx.area << endl;

    vector<int> houses;

    for(int i = c - 1; i >= 0; --i) {
        houses.push_back(mx.size);
        if(mx.from == -1) break;
        else mx = dp[i - 1][mx.from];
    }

    reverse(houses.begin(), houses.end());

    for(auto h : houses) cout << 2*h << endl;
}
