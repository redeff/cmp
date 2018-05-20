#include "seg_tree.h"

#include <bits/stdc++.h>
using namespace std;


struct Times {
    int operator()(int a, int b) {
        return a * b;
    }
};

struct Plus {
    int operator()(int a, int b) {
        return a + b;
    }
};

int main() {
    SegTree<int, int, int, Plus, Times, Times> st(10, 1, 1);
    st.st(1, 5, 2);
    std::cout << st.gt(1, 5);
}
