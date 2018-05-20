#include <bits/stdc++.h>
#include "seg_tree.h"

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

struct Func {
    int val;
    bool st;
};

struct Data {
    int val;
    int am;
};

int main() {
    auto apply = [&](Data a, Func f) -> Data {
        if(f.st) return {a.am * f.val, a.am};
        else return {a.val + a.am * f.val, a.am};
    };

    auto compose = [&](Func a, Func b) -> Func {
        if(b.st) return b;
        else return {b.val + a.val, a.st};
    };

    auto reduce = [&](Data a, Data b) -> Data {
        return {a.val + b.val, a.am + b.am};
    };

    SegTree<int, Data, Func, decltype(apply), decltype(reduce), decltype(compose)> st(1000000, {0, 1}, {0, 0}, {0, false}, apply, reduce, compose);
    // st.st(0, 10, {0, true});
    st.st(0, 200000, {2, false});
    st.st(7, 9, {11, false});
    std::cout << st.gt(2000, 900000).val;
}
