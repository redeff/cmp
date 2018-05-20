#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const ll MOD = 1e9 + 7;

enum Color {
    BLACK,
    WHITE
};

struct Node;

// Adjacency list of a tree with root at 0
vector<vector<Node>> tree;
vector<Color> colors;

vector<ll> whites;
vector<ll> blacks;


// Node of a rooted tree
struct Node {
    size_t ix;
    Node(): ix(-1) {}
    Node(size_t ix): ix(ix) {}

    size_t size() {
        return tree[ix].size();
    }

    bool unit() {
        return size() == 0;
    }

    // Color of the node
    Color color() {
        return colors[ix];
    }

    // Return number of ways of cutting current tree if Node were white
    ll & white() {
        return whites[ix];
    }

    // Return number of ways of cutting current tree if Node were black
    ll & black() {
        return blacks[ix];
    }

    // Number of ways of cutting a tree consisting of the tree rooted
    // in Node with a single black parent
    ll parent_black() {
        if(color() == BLACK) return black();
        else return (black() + white()) % MOD;
    }

    // Return number of ways of cutting current tree
    ll & self() {
        if(color() == BLACK) return black();
        else return white();
    }

    Node ith(size_t i) {
        return tree[ix][i];
    }

    void cut() {
        if(unit()) {
            black() = 1;
            white() = 0;
        } else {
            vector<ll> prefixes(size()); 
            prefixes[0] = 1;
            for(int i = 1; i < size(); ++i) {
                prefixes[i] = (ith(i - 1).parent_black() * prefixes[i - 1]) % MOD;
            }

            vector<ll> suffixes(size()); 
            suffixes[size() - 1] = 1;
            for(int i = size() - 2; i >= 0; --i) {
                suffixes[i] = (ith(i + 1).parent_black() * suffixes[i + 1]) % MOD;
            }

            black() = 1;
            for(int i = 0; i < size(); ++i) {
                black() *= ith(i).parent_black();
                black() %= MOD;
            }

            white() = 0;
            for(int i = 0; i < size(); ++i) {
                white() += ((prefixes[i] * suffixes[i]) % MOD * ith(i).self()) % MOD;
                white() %= MOD;
            }
        }
    }
};

int main() {
    int n;
    cin >> n;

    tree = vector<vector<Node>>(n);
    colors = vector<Color>(n);

    whites = vector<ll>(n);
    blacks = vector<ll>(n);

    for(int i = 0; i < n - 1; ++i) {
        int p;
        cin >> p;
        tree[p].emplace_back();
        tree[p].back().ix = i + 1;
    }

    colors = vector<Color>(n);
    for(int i = 0; i < n; ++i){
        int c;
        cin >> c;
        colors[i] = c == 1 ? BLACK : WHITE;
    }

    for(int i = n - 1; i >= 0; --i) {
        Node(i).cut();
    }

    Node root(0);
    cout << root.self() << endl;
}
