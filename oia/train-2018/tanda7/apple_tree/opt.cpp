#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const ll MOD = 1e9 + 7;

enum Color {BLACK, WHITE};

struct ColorInfo {
    ll white;
    ll black;
    ll get(Color color) {
        if(color == BLACK) return black; else return white;
    }

    ColorInfo(ll white, ll black): white(white), black(black) {}
    ColorInfo(): white(-1), black(-1) {}
};

struct Ix;

vector<vector<Ix>> tree;
vector<Color> colors;
vector<ColorInfo> dp;

struct Ix {
    size_t ix;
    Ix(): ix(-1) {}
    Color color() {
       return colors[ix];
    }

    size_t branches() {
        return tree[ix].size();
    }

    Ix ith(size_t i) {
        return tree[ix][i];
    }

    bool unit() {
        return tree[ix].size() == 0;
    }

    ColorInfo cut() {
        if(dp[ix].white != -1) return dp[ix];
        if(unit()) return ColorInfo(0, 1);    

        vector<ll> if_parent_black(branches());
        for(size_t i = 0; i < branches(); ++i) {
            Ix ith_child = ith(i);
            if(ith_child.color() == BLACK) {
                if_parent_black[i] = ith_child.cut().black;
            } else {
                if_parent_black[i] = ith_child.cut().black + ith_child.cut().white;
            }
        }

        vector<ll> prefixes(branches());
        prefixes[0] = 1;
        for(size_t i = 1; i < branches(); ++i) {
            prefixes[i] = prefixes[i - 1] * if_parent_black[i - 1];
            prefixes[i] %= MOD;
        }

        vector<ll> suffixes(branches());
        suffixes[branches() - 1] = 1;
        for(ll i = branches() - 2; i >= 0; --i) {
            suffixes[i] = suffixes[i + 1] * if_parent_black[i + 1];
            suffixes[i] %= MOD;
        }

        ll product = 1;
        for(ll i = 0; i < branches(); ++i) {
            product *= if_parent_black[i];
            product %= MOD;
        }

        ll if_white = 0;

        for(ll i = 0; i < branches(); ++i) {
            ll this_case = prefixes[i] * suffixes[i];
            this_case %= MOD;

            this_case *= ith(i).cut().get(ith(i).color());

            this_case %= MOD;

            if_white += this_case;
            if_white %= MOD;
        }

        dp[ix] = ColorInfo(if_white, product);
        return dp[ix];
    }
};

int main() {
    int n;
    cin >> n;

    tree = vector<vector<Ix>>(n);
    dp = vector<ColorInfo>(n, ColorInfo());

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
        Ix root;
        root.ix = i;
        root.cut();
    }

    Ix root;
    root.ix = 0;
    cout << root.cut().get(root.color()) << endl;
}
