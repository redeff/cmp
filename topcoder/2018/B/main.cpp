#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Point {
    ll x;
    ll y;
};

vector<Point> horse = {
    Point {1, 2},
    Point {-1, 2},
    Point {1, -2},
    Point {-1, -2},
    Point {2, 1},
    Point {-2, 1},
    Point {2, -1},
    Point {-2, -1},
};

Point operator-(Point a, Point b) {
    return Point {a.x - b.x, a.y - b.y};
}

bool bishop(Point p) {
    return p.x == p.y || p.x == -p.y;
}

struct Knishop {
    int getShortestPath(int x1, int y1, int x2, int y2) {
        Point p = {x1 - x2, y1 - y2};
        if(p == {0, 0}) return 0;
        if(bishop(p)) return 1;
        for(h : horse) if(h - p == Point {0, 0}) return 1;
        for(h : horse) if(bishop(h - p)) return 2;
        if((p.x + p.y) % 2 == 0) return 2;
        return 3;
    }
};
