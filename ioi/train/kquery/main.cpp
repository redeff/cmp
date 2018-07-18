#include <bits/stdc++.h>
using namespace std;

void ft_set(int n, vector<int> &ft) {
    for(int i = n; i < ft.size(); i += i & -i) {
        ft[i]++;
    }
}

int ft_get(int n, vector<int> &ft) {
    int total = 0;
    for(int i = n; i; i -= i & -i) {
        total += ft[i];
    }

    return total;
}

struct Query {
    int a;
    int b;
    int k;
    int res;
};

bool operator>(Query q1, Query q2) {
    return q1.k > q2.k;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    /*
    int n;
    cin >> n;
    vector<int> ft(n+1, 0);
    while(true) {
        int a, b;
        cin >> a;
        if(a == -1) break;
        cin >> b;
        if(a == 0) ft_set(b, ft);
        else cout << ft_get(b, ft) << endl;
    }
    */

    int n;
    cin >> n;
    vector<int> ns(n);
    for(int i = 0; i < n; ++i) {
        cin >> ns[i];
    }

    vector<int> ft(n+1, 0);

    vector<int> ord(n);
    for(int i = 0; i < n; ++i) ord[i] = i;
    sort(ord.begin(), ord.end(), [&](int a, int b) {return ns[a] > ns[b];});

    int q;
    cin >> q;
    vector<Query> qs(q);
    for(int i = 0; i < q; ++i) {
        cin >> qs[i].a >> qs[i].b >> qs[i].k;
        qs[i].res = -1;
    }

    
    vector<int> qord(q);
    for(int i = 0; i < q; ++i) qord[i] = i;
    sort(qord.begin(), qord.end(), [&](int a, int b) {return qs[a] > qs[b];});

    int curr_q = 0;
    int curr_n = 0;
    while(curr_q < q) {
        if(curr_n == n || ns[ord[curr_n]] <= qs[qord[curr_q]].k) {
            Query q = qs[qord[curr_q]];
            qs[qord[curr_q]].res = ft_get(q.b, ft) - ft_get(q.a - 1, ft);
            curr_q++;
        } else {
            ft_set(ord[curr_n] + 1, ft);
            curr_n++;
        }
    }

    for(auto q : qs) cout << q.res << "\n";
}
