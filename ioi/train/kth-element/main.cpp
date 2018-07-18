#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Node {
    int ch[2];
    int val;
};

int flog(int n) {
    return 8 * sizeof(int) - 1 - __builtin_clz(n);
}

struct Dummy {
    int ch;
    int index;
};
// Se rompe con n == 1 ya que es la raiz del arbol
Dummy descend(int n) {
    int f = flog(n);
    f--;
    return {(n < (2 << f) + (1 << f)) ? 0 : 1, n - (1 << f)};
}

// Segtree Persistente.  Uuuu
int update(int head, int n, int delta, vector<Node> &st) {
    if(n == 1) {
        int siz = st.size();
        st.push_back({{siz, 0}, st[head].val + delta}); 
        return siz;
    } else {
        auto p = descend(n);
        int rec = update(st[head].ch[p.ch], p.index, delta, st);
        int siz = st.size();
        Node new_node = st[head];
        new_node.val += delta;
        new_node.ch[p.ch] = rec;
        st.push_back(new_node);
        return siz;
    }
}

int query(int head, int index, vector<Node> &st) {
    if(index == 1) return st[head].val;
    auto p = descend(index);
    int total = 0;
    // La única asimetría
    if(p.ch == 1) total += st[st[head].ch[0]].val;
    return total + query(st[head].ch[p.ch], p.index, st);
}

void debug(int head, vector<Node> &st) {
    // cerr << "(";
    // cerr << st[head].val << " ";
    if(st[head].ch[0] != head && st[head].ch[1] != head) {
        debug(st[head].ch[0], st);
        debug(st[head].ch[1], st);
    } else {

        cerr << st[head].val << " ";
    }
    // cerr << ")";
}

vector<Node> st = {{{0, 0}, 0}};

const int BIG = (1 << 18) + 1;

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
        heads.push_back(update(heads.back(), ord[i] + BIG, 1, st));
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
            int amount = query(heads[mid], BIG + b, st);
            amount -= query(heads[mid], BIG + a - 1, st);
            if(amount < k) lo = mid;
            else hi = mid;
        }

        cout << ns[ord[lo]] << endl;
    }
}
