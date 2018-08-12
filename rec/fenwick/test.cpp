#include <bits/stdc++.h>
using namespace std;

namespace int_ft {
    typedef int T;
    T op(T a, T b) {return a + b;}
    const T zero = 0;
    #include "lib.h"
}

using namespace int_ft;

int main() {
    auto ft = init(10);
    update(0, 10, ft);
    update(1, 10, ft);
    update(9, 10, ft);

    cout << query(0, ft) << endl;
    cout << query(1, ft) << endl;
    cout << query(2, ft) << endl;
    cout << query(8, ft) << endl;
    cout << query(9, ft) << endl;
    cout << query(10, ft) << endl;
    
}
