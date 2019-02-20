#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const ll MOD = 1e9 + 7;

ll mod_inv(ll a) {
    ll i = 1;
    ll b = a;

    ll total = 1;

    while(i <= MOD - 2) {
        if(i & (MOD - 2)) {
            total *= b;
        }

        b = b * b;
        b %= MOD;

        i *= 2;
    }

    return total;
}

struct Tree {
    bool color;
    vector<Tree> children;
    bool unit() {
        return children.empty();
    }

    int branches() {
        return children.size();
    }
    
    bool is_black() {
        return color;
    }
};

vector<pair<ll, ll>> dpdp;
pair<ll, ll> calc(Tree &tree) {
    if(tree.unit()) return {1, 0};

    // cerr << "BEGIN" << endl;

    vector<pair<ll, ll>> dp;
    ll b = tree.branches();

    // For each children, call calc and store the result
    for(ll i = 0; i < b; ++i) {
        dp.push_back(calc(tree.children[i]));
    }

    /*
    ll if_black = 1;
    ll if_white = 0;

    ll total = 1;
    */

    // For each child, number of ways of coloring that child
    // with a black node attatched to the root
    vector<ll> if_parent_black(b);

    for(ll i = 0; i < b; ++i) {
        Tree &subtree = tree.children[i];
        if(subtree.is_black()) {
            if_parent_black[i] = dp[i].first;
            /*
            if_black *= dp[i].first;
            if_black %= MOD;
            */
        } else {
            if_parent_black[i] = dp[i].first + dp[i].second;
            /*
            if_black *= dp[i].first + dp[i].second;
            if_black %= MOD;
            */
        }
    }

    vector<ll> prefixes(b);
    prefixes[0] = 1;
    for(ll i = 1; i < b; ++i) {
        prefixes[i] = prefixes[i - 1] * if_parent_black[i - 1];
        prefixes[i] %= MOD;
    }

    vector<ll> suffixes(b);
    suffixes[b - 1] = 1;
    for(ll i = b - 2; i >= 0; --i) {
        suffixes[i] = suffixes[i + 1] * if_parent_black[i + 1];
        suffixes[i] %= MOD;
    }

    ll product = 1;
    for(ll i = 0; i < b; ++i) {
        product *= if_parent_black[i];
        product %= MOD;
    }

    ll if_white = 0;

    for(ll i = 0; i < b; ++i) {
        ll this_case = prefixes[i] * suffixes[i];
        this_case %= MOD;

        if(tree.children[i].is_black())
            this_case *= dp[i].first;
        else
            this_case *= dp[i].second;

        this_case %= MOD;

        if_white += this_case;
        if_white %= MOD;
    }

    // cerr << "RETURN " << product << ", " << if_white << endl;
    return {product, if_white};
}

Tree constr(vector<vector<int>> &tree, vector<bool> &colors, int root) {
    vector<Tree> children(tree[root].size());
    for(int i = 0; i < tree[root].size(); ++i) {
        children[i] = constr(tree, colors, tree[root][i]); 
    }

    Tree rtn;
    rtn.children = children;
    rtn.color = colors[root];

    return rtn;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; ++i) {
        int p;
        cin >> p;
        adj[p].push_back(i + 1);
    }

    vector<bool> colors(n);
    for(int i = 0; i < n; ++i){
        int c;
        cin >> c;
        colors[i] = c == 1;
    }

    Tree tree = constr(adj, colors, 0);

    auto p = calc(tree);
    if(tree.is_black()) cout << p.first << endl;
    else cout << p.second << endl;
    // cout << p.first << " " << p.second << endl;
}
