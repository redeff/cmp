#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

typedef int T;
T op(T a, T b) {return a + b;}
T zero = 0;

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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<ll> ns(n);
    for(int i = 0; i < n; ++i) cin >> ns[i];

    vector<int> ord(n);
    for(int i = 0; i < n; ++i) ord[i] = i;
    sort(ord.begin(), ord.end(), [&](int a, int b) {return ns[a] < ns[b];});
    vector<int> heads = {0};
    for(int i = 0; i < n; ++i) {
        heads.push_back(update(heads.back(), ord[i], 1));
    }

    /*
    for(int i = 0; i < n; ++i) {
        debug(heads[i], st); cerr << endl;
        cerr << i << " - ";
        for(int j = 0; j < n; ++j) {
            cerr << query(heads[i], BIG + j, st) << " ";
        }
        cerr << endl;
    }
    */

    for(int i = 0; i < m; ++i) {
        int a, b, k;
        cin >> a >> b >> k;
        a--; b--;

        int lo = 0;
        int hi = n;

        while(hi - lo > 1) {
            int mid = (hi + lo) / 2;
            int amount = query(heads[mid], b);
            amount -= query(heads[mid], a - 1);
            if(amount < k) lo = mid;
            else hi = mid;
        }

        cout << ns[ord[lo]] << endl;
    }
}
