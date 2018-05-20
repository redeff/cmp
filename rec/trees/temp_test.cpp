#include <bits/stdc++.h>
using namespace std;

template<class T>
struct wrapper {
    T inner;
    wrapper(T inner): inner(inner) {
        // auto t = new wrapper<T>(5);
    }

    template <class F>
    void ma(F f) {
        inner = f(inner);
    }
};



int main() {
    auto t = new wrapper<int>(5);
    auto fun = [&](int i) { return i + 1; };
    t->ma(fun);
    cout << (t->inner) << endl;
}
