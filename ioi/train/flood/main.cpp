#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x;
    int y;
};

struct Wall {
    int a;
    int b;
};

int main() {
    int n;
    cin >> n;

    vector<Point> ns(n);
    for(int i = 0; i < n; ++i) {
        cin >> ns[i].x >> ns[i].y;
    }

    int w;
    cin >> w;
    vector<Wall> ws(w);

    auto hor = [&](Wall wall) -> bool {
        return ns[wall.a].y == ns[wall.b].y;
    };

    for(int i = 0; i < w; ++i) {
        cin >> ws[i].a >> ws[i].b;
        ws[i].a--;
        ws[i].b--;
        if(ns[ws[i].a].x > ns[ws[i].b].x) swap(ws[i].a, ws[i].b);
        if(ns[ws[i].a].y > ns[ws[i].b].y) swap(ws[i].a, ws[i].b);

        /*
        if(hor(ws[i])) {
            joints[ws[i].a][0] = i;
            joints[ws[i].b][2] = i;
        } else {
            joints[ws[i].a][1] = i;
            joints[ws[i].b][3] = i;
        }
        */
    }

    struct Conn {
        int to;
        int wei;
    };

    vector<vector<Conn>> corners(4*n);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 4; ++j) {
            corners[4*i + j] = {{4*i + (j+3)%4, 0}, {4*i + (j+1)%4, 0}};
        }
    }

    for(Wall wall : ws) {
        if(hor(wall)) {
            corners[4*wall.a + 0][0].wei = 1;
            corners[4*wall.a + 3][1].wei = 1;

            corners[4*wall.b + 2][0].wei = 1;
            corners[4*wall.b + 1][1].wei = 1;

            corners[4*wall.a + 0].push_back({4*wall.b + 1, 0});
            corners[4*wall.b + 1].push_back({4*wall.a + 0, 0});

            corners[4*wall.a + 3].push_back({4*wall.b + 2, 0});
            corners[4*wall.b + 2].push_back({4*wall.a + 3, 0});
        } else {
            corners[4*wall.a + 1][0].wei = 1;
            corners[4*wall.a + 0][1].wei = 1;

            corners[4*wall.b + 3][0].wei = 1;
            corners[4*wall.b + 2][1].wei = 1;

            corners[4*wall.a + 0].push_back({4*wall.b + 3, 0});
            corners[4*wall.b + 3].push_back({4*wall.a + 0, 0});

            corners[4*wall.a + 1].push_back({4*wall.b + 2, 0});
            corners[4*wall.b + 2].push_back({4*wall.a + 1, 0});
        }
    }

    const int INF = 333333;
    vector<int> time(4*n, INF);

    vector<int> index(4*n);
    for(int i = 0; i < 4*n; ++i) index[i] = i;
    auto hei = [&](int i) {
        return ns[i/4].y - (i % 4) / 2;
    };

    sort(index.begin(), index.end(), [&](int a, int b) {return hei(a) < hei(b);});

    function<void(int)> flood = [&](int node) {
        vector<int> curr = {node};
        time[node] = 0;
        vector<int> nxt = {};
        while(!curr.empty()) {
            while(!curr.empty()) {
                int k = curr.back();
                curr.pop_back();
                for(Conn c : corners[k]) if(time[c.to] > time[k] + c.wei) {
                    time[c.to] = time[k] + c.wei;
                    if(c.wei == 1)  nxt.push_back(c.to);
                    else           curr.push_back(c.to);
                }
            }
            swap(curr, nxt);
            nxt.clear();
        }
    };

    for(int j = 0; j < 4*n; ++j) {
        int i = index[j];
        if(time[i] == INF) {
            flood(i); 
        }
    }

    vector<int> fin;
    for(int i = 0; i < w; ++i) {
        if((hor(ws[i]) && time[4*ws[i].a + 0] == time[4*ws[i].a + 3])
                || (!hor(ws[i]) && time[4*ws[i].a + 0] == time[4*ws[i].a + 1])) {
                fin.push_back(i);
        }
    }

    cout << fin.size() << endl;
    for(int i : fin) cout << i+1 << endl;
}
