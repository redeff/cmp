// typedef T int;
// op : (T, T) -> T
// zero : T

struct Node {
    int ch[2];
    T val;
};

vector<Node> st = {{{0, 0}, zero}};
void init() {
    st = {{{0, 0}, zero}};
}

struct Dummy {
    int ch;
    int index;
};

int flog(int n) {
    return 8 * sizeof(int) - 1 - __builtin_clz(n);
}

// Se rompe con n == 1 ya que es la raiz del arbol
Dummy descend(int n) {
    int f = flog(n);
    f--;
    return {(n < (2 << f) + (1 << f)) ? 0 : 1, n - (1 << f)};
}

int hidden_update(int head, int n, T delta) {
    if(n == 1) {
        int siz = st.size();
        st.push_back({{siz, 0}, op(st[head].val, delta)}); 
        return siz;
    } else {
        auto p = descend(n);
        int rec = hidden_update(st[head].ch[p.ch], p.index, delta);
        int siz = st.size();
        Node new_node = st[head];
        new_node.val = op(new_node.val, delta);
        new_node.ch[p.ch] = rec;
        st.push_back(new_node);
        return siz;
    }
}

T hidden_query(int head, int index) {
    if(index == 1) return st[head].val;
    auto p = descend(index);
    int total = 0;
    // La única asimetría
    if(p.ch == 1) total = op(total, st[st[head].ch[0]].val);
    return op(total, hidden_query(st[head].ch[p.ch], p.index));
}

int gamma(int index) {
    int k = flog(index);
    int ones = (1 << (k + 1)) - 1;
    return (ones << (k + 1)) + (index ^ (1 << k));

}

int delta(int index) {
    int k = flog(index);
    int g = gamma(k);
    return (g << k) + (index ^ (1 << k));
}

int trans(int index) {
    if(index >= 0) {
        index += 2;
        int res = delta(index);
        return res + (2 << flog(res));
    } else {
        index -= 1;
        index *= -1;
        int res = delta(index);
        int f = flog(res);
        return (res + (1 << f)) ^ ((1 << f) - 1);
    }
}

int update(int head, int n, T delta) {
    return hidden_update(head, trans(n), delta);    
}

T query(int head, int n) {
    return hidden_query(head, trans(n));    
}
