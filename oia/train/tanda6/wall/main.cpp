#include <bits/stdc++.h>
using namespace std;
int const INF = 333333333;

template <class C>
struct Fold {
    vector<C> ns;
    vector<C> fold;
    vector<int> index_map;
    C (*f)(C, C);
    C id;

    void create_index_map(int index) {
        if(index < ns.size()) {
            index_map.push_back(index);
            create_index_map(2 * index + 1);
            create_index_map(2 * index + 2);
        }
    }

    C get_at(int index) {
        return index < ns.size() ? fold[index] : id;
    }

    void update(int index) {
        // cout << index << " " << fold[index] << " ";
        fold[index] = f(ns[index], f(get_at(2 * index + 1), get_at(2 * index + 2)));
        // cout << fold[index] << endl;
        if(index != 0) update((index - 1) / 2);
    }

public:

    Fold(int n, C nid, C (*f)(C, C)) : id(nid), f(f) {
        ns = vector<C>(n, id);
        fold = vector<C>(n, id);
        create_index_map(0);
    }

    void st(int index_out, C nval) {
        int index = index_map[index_out];
        ns[index] = nval;
        update(index);
    }

    C gt() {
        return fold[0];
    }
};

pair<int, int> sequence(pair<int, int> a, pair<int, int> b) {
    if(a.second < b.first) return {b.first, b.first};
    if(b.second < a.first) return {b.second, b.second};
    return {max(a.first, b.first), min(a.second, b.second)};
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int final_height[]) {
    /*
    cout << left[0] << endl;
    cout << height[0] << endl;
    cout << op[0] << endl;
    */
    vector<pair<int, int>> sects {};
    for(int i = 0; i < k; ++i) {
        if(op[i] == 1) {
            sects.emplace_back(height[i], INF);
        } else {
            sects.emplace_back(0, height[i]);
        }
        int s = i;
        // cout << sects[i].first << " : " << sects[i].second << endl;
    }
    vector<vector<int>> starts_at(n);
    vector<vector<int>> ends_at(n);

    for(int i = 0; i < k; ++i) {
        starts_at[left[i]].push_back(i);
        ends_at[right[i]].push_back(i);
    }
    /*
    vector<int> sorted_start;
    for(int i = 0; i < k; ++i) sorted_start.push_back(i);
    sort(sorted_start.begin(), sorted_start.end(), [&](int a, int b) {return right[a] < right[b]});

    vector<int> sorted_end;
    for(int i = 0; i < k; ++i) sorted_end.push_back(i);
    sort(sorted_end.begin(), sorted_end.end(), [&](int a, int b) {return left[a] < left[b]});
    */

    auto f = Fold<pair<int, int>>(k, make_pair(0, INF), sequence);
    for(int i = 0; i < n; ++i) {
        for(int s : starts_at[i]) {
            // cout << sects[s].first << " - " << sects[s].second << endl;
            f.st(s, sects[s]);
        } 

        // cout << f.gt().first << " ? " << f.gt().second << endl;
        final_height[i] = sequence(make_pair(0, 0), f.gt()).first;

        for(int s : ends_at[i]) {
            f.st(s, f.id);
        } 
    }
}

/*
int main() {
    int n = 10;

    vector<int> out(n);
    int k = 6;
    vector<int> height {4, 1, 5, 3, 5, 0};
    vector<int> type {1, 2, 2, 1, 1, 2};
    vector<int> left {1, 4, 3, 0, 2, 6};
    vector<int> right {8, 9, 6, 5, 2, 7};
    buildWall(n, k, &type[0], &left[0], &right[0], &height[0], &out[0]);
    for(auto o : out) {
        cout << o << endl;
    } cout << endl;

    *//*
    auto f = Fold<int>(10, 0, add);

    f.st(0, 10);
    f.st(0, 20);
    f.st(0, 2);
    f.st(4, 3);
    cout << f.gt() << endl;
    *//*
}
*/
