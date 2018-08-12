#include <bits/stdc++.h>
using namespace std;

struct Line {
    int start;
    int vel;
};

bool orient(Line l1, Line l2, Line l3) {
    assert(l1.start < l2.start);
    assert(l2.start < l3.start);

    // ta = (l2.start - l1.start) / (l1.vel - l2.vel);
    return (l2.start - l1.start) * (l1.vel - l3.vel) < (l3.start - l1.start) * (l1.vel - l2.vel);
}

int main() {
     
}
