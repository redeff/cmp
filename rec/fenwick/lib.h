// typedef int T;
// T op(T a, T b) {return a + b;}
// const T zero = 0;

vector<T> init(int n) {
    return vector<T>(n + 1, zero);
}

void update(int p, T delta, vector<T> &ft) {
    p++;
    assert(p < ft.size());
    for(int i = p; i < ft.size(); i += i & -i) {
        ft[i] = op(ft[i], delta);
    }
}

T query(int p, vector<T> &ft) {
    // p++;
    assert(p < ft.size());
    T total = zero;
    for(int i = p; i; i -= i & -i) {
        total = op(total, ft[i]);
    }

    return total;
}
