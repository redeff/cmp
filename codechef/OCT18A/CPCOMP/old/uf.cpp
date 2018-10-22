#include <bits/stdc++.h>
using namespace std;

const int EXP = 18;
const int BOUND = 1 << EXP;

vector<int> mu;
vector<int> radical;
vector<int> squarefree;

struct Uf {
    int color;
    int deg;
};

vector<Uf> uf;

vector<bool> exists;
vector<int> amount;

int color(int a) {
    int t = a;
    while(uf[a].color != a) a = uf[a].color;
    for(int i = t; i != a;) {
        int j = i;
        i = uf[j].color;
        uf[j].color = a;
    }

    return a;
}

bool merge(int a, int b) {
    a = color(a);
    b = color(b);
    if(a == b) return false;
    if(uf[a].deg < uf[b].deg) swap(a, b);
    uf[b].color = a;
    if(uf[a].deg == uf[b].deg) uf[a].deg++;
    return true;
}

void init() {
    mu = vector<int>(BOUND, 1);
    radical = vector<int>(BOUND, 1);

    for(int i = 2; i < BOUND; ++i) {
        if(radical[i] == 1) {
            for(int j = i; j < BOUND; j += i) {
                mu[j] *= -1;
                radical[j] *= i;
            }

            if(i <= BOUND / i) for(int j = i * i; j < BOUND; j += i * i) {
                mu[j] = 0;
            }
        }
    }
    for(int i = 1; i < BOUND; ++i) if(radical[i] == i) {
        squarefree.push_back(i);
    }

    uf = vector<Uf>(BOUND);
    for(int i = 0; i < BOUND; ++i) {
        uf[i].color = i;
        uf[i].deg = 0;
    }

    exists = vector<bool>(BOUND, false);
    amount = vector<int>(BOUND, 0);
}

vector<int> with_exp(int e) {
    vector<int> color_sum(BOUND);
    vector<int> out(BOUND, 0);

    for(int m : squarefree) {
        vector<int> ds;
        for(int d = m; d < BOUND; d += m) if(exists[d]) ds.push_back(d);

        for(int d : ds) {
            color_sum[color(d)] = 0;
        }

        int total = 0;
        for(int d : ds) {
            int disc = ((d & (1 << e)) == 0) ? 1 : 0;
            total += mu[m] * disc;

            color_sum[color(d)] += mu[m] * disc;
        }

        for(int d : ds) {
            out[d] += total - color_sum[color(d)];
        }
    }

    return out;
}

bool step() {
    vector<int> low(BOUND, 0);
    for(int e = 0; e < EXP; ++e) {
        vector<int> deg = with_exp(e);
        for(int i = 0; i < BOUND; ++i) {
            if(deg[i] == 0) low[i] += 1 << e; 
        }
    }

    bool changed = false;
    for(int i = 0; i < BOUND; ++i) if(exists[i] && low[i] < BOUND - 1) {
        cerr << i << " " << low[i] << endl;
        if(merge(i, low[i])) changed = true;
    }

    return changed;
}


int main() {
    int n;
    cin >> n;

    init();    
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        cerr << a << " - " << radical[a] << endl;
        exists[radical[a]] = true;
        amount[radical[a]]++;
    }

    while(step());

    unordered_map<int, int> colors;
    for(int i = 0; i < BOUND; ++i) if(exists[i]) colors[color(i)] += 1;
    
    int total = colors.size();
    for(int i = 0; i < BOUND; ++i) if(exists[i] && colors[color(i)] == 1) total += amount[i] - 1;
    cout << total << endl;
}
