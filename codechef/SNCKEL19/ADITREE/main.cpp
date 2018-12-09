#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
 
template<class T, int SZ> struct LazySegTree {
    T sum[2*SZ]/*, mn[2*SZ]*/, lazy[2*SZ]; // set SZ to a power of 2
 
    LazySegTree() {
        for(int i = 0; i < 2*SZ; ++i) {
            sum[i] = 1;
            lazy[i] = 1;
        }
    }
 
    void push(int ind, int L, int R) {
        sum[ind] *= lazy[ind];
        // mn[ind] += lazy[ind];
        if (L != R) lazy[2*ind] *= lazy[ind], lazy[2*ind+1] *= lazy[ind];
        lazy[ind] = 1;
    }
 
    void pull(int ind) {
        sum[ind] = sum[2*ind]+sum[2*ind+1];
        // mn[ind] = min(mn[2*ind],mn[2*ind+1]);
    }
 
    void build() {
        for(int i = SZ-1;i>=0; i--){
            pull(i);
        }
    }
 
    T qsum(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
        push(ind,L,R);
        if (lo > R || L > hi) return 0;
        if (lo <= L && R <= hi) return sum[ind];
 
        int M = (L+R)/2;
        return qsum(lo,hi,2*ind,L,M) + qsum(lo,hi,2*ind+1,M+1,R);
    }
 
    /*
    T qmin(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
        push(ind,L,R);
        if (lo > R || L > hi) return INF;
        if (lo <= L && R <= hi) return mn[ind];
 
        int M = (L+R)/2;
        return min(qmin(lo,hi,2*ind,L,M), qmin(lo,hi,2*ind+1,M+1,R));
    }
    */
 
    void upd(int lo, int hi, long long inc, int ind = 1, int L = 0, int R = SZ-1) {
        push(ind,L,R);
        if (hi < L || R < lo) return;
        if (lo <= L && R <= hi) {
            lazy[ind] = inc;
            push(ind,L,R);
            return;
        }
 
        int M = (L+R)/2;
        upd(lo,hi,inc,2*ind,L,M); upd(lo,hi,inc,2*ind+1,M+1,R);
        pull(ind);
    }
};
vector<vector<int>> graph;
template <class T, int V>
class HeavyLight {
public:
  int parent[V], heavy[V], depth[V];
  int root[V], treePos[V];
  LazySegTree<T, V> tree;
 
  template <class G>
  int dfs(const G& graph, int v) {
    int size = 1, maxSubtree = 0;
    for (int u : graph[v]) if (u != parent[v]) {
      parent[u] = v;
      depth[u] = depth[v] + 1;
      int subtree = dfs(graph, u);
      if (subtree > maxSubtree) heavy[v] = u, maxSubtree = subtree;
      size += subtree;
    }
    return size;
  }
 
  template <class BinaryOperation>
  void processPath(int u, int v, BinaryOperation op) {
    for (; root[u] != root[v]; v = parent[root[v]]) {
      if (depth[root[u]] > depth[root[v]]) swap(u, v);
      op(treePos[root[v]], treePos[v] + 1);
    }
    if (depth[u] > depth[v]) swap(u, v);
    op(treePos[u], treePos[v] + 1);
  }
 
  template <class G>
  void init(const G& graph) {
    int n = graph.size();
    fill_n(heavy, n, -1);
    parent[0] = -1;
    depth[0] = 0;
    dfs(graph, 0);
    for (int i = 0, currentPos = 0; i < n; ++i)
      if (parent[i] == -1 || heavy[parent[i]] != i)
        for (int j = i; j != -1; j = heavy[j]) {
          root[j] = i;
          treePos[j] = currentPos++;
        }
    tree.build();
  }
 
  void set(int v, const T& value) {
    tree.set(treePos[v], value);
  }
 
  void modifyPath(int u, int v, const T& value) {
    processPath(u, v, [this, &value](int l, int r) { tree.upd(l, r-1, value); });
  }
 
  long long queryPath(int u, int v) {
    long long res =0;
    processPath(u, v, [this, &res](int l, int r) { res += (tree.qsum(l, r-1)); });
    return res;
  }
};
 
HeavyLight<int, 1<<18> H;
 
int main() {
	// H.modifyPath(4, 5, -1);
    /*
	cout << H.queryPath(4, 6) << endl;
	cout << H.queryPath(4, 5) << endl;
	cout << H.queryPath(4, 4) << endl;
	cout << H.queryPath(3, 3) << endl;
	cout << H.queryPath(5, 5) << endl;
	cout << H.queryPath(7, 7) << endl;
	cout << H.queryPath(0, 0) << endl;
    */
    /*
    cout << H.queryPath(2, 1) << endl;
    cout << H.queryPath(2, 2) << endl;
    cout << H.queryPath(1, 1) << endl;
    cout << H.queryPath(2, 6) << endl;
    */
	// H.modifyPath(0, 2, -1);
	// H.modifyPath(5, 0, -1);
    /*
    cout << H.tree.qsum(0, 0) << endl;
    cout << H.tree.qsum(1, 1) << endl;
    cout << H.tree.qsum(2, 2) << endl;
    cout << H.tree.qsum(3, 3) << endl;
    cout << H.tree.qsum(4, 4) << endl;
    cout << H.tree.qsum(5, 5) << endl;
    */

    /*
    LazySegTree<int, 1<<17> S;
    S.build();
    S.upd(1, 10, -1);
    cout << S.qsum(1, 20) << endl;
    */

    int n;
    cin >> n;
	graph.resize(n+1);
	for(int i = 0; i<n-1; i++) {
	    int a,b; cin >> a >> b;
	    a--; b--;
	    graph[a].push_back(b); graph[b].push_back(a);
	}
	H.init(graph);

    // cerr << "inited" << endl;

    int m;
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        H.modifyPath(a, 0, -1);
        H.modifyPath(b, 0, -1);
        cout << (-H.tree.qsum(0, n-1) + n)/2 << endl;
    }
}
