#include <bits/stdc++.h>
using namespace std;

namespace st {
    typedef int T;
    T op(T a, T b) {return a + b;}
    const T zero = 0;

    #include "lib.h"
}

int main() {
    st::init();
    auto h = st::update(0, 1000, 13);
    cout << st::query(h, 1000) << endl;
    cout << st::query(h, 999) << endl;
    h = st::update(h, -10, 13);
    cout << st::query(h, 1000) << endl;
    cout << st::query(h, 0) << endl;
    cout << st::query(h, -10) << endl;
    cout << st::query(h, -11) << endl;

}
