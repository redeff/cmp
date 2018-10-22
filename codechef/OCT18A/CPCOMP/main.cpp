#include <bits/stdc++.h>
using namespace std;

// const int BOUND = 200003;
const int BOUND = 1 << 18;

vector<int> mu;
vector<int> radical;
vector<int> primes;
vector<int> squarefree;
vector<vector<int>> das;

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
    primes = vector<int>(BOUND, 0);

    for(int i = 2; i < BOUND; ++i) {
        if(radical[i] == 1) {
            for(int j = i; j < BOUND; j += i) {
                mu[j] *= -1;
                radical[j] *= i;
                primes[j] += 1;
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

struct Entry {
    // int m;
    int mu;
    vector<int> *v;
};

vector<int> do_stuff(vector<vector<Entry>> &out) {

    vector<int> low(BOUND);
    for(int i = 0; i < BOUND; ++i) if(exists[i]) {
        int lo = 0;
        int hi = BOUND;
        while(hi - lo > 1) {
            // int mid = (hi + 7 * lo) / 8;
            int mid = (hi + lo) / 2;
            int total = 0;
            for(Entry e : out[i]) {
                // cerr << "eeh " << lo << " " << hi << endl;
                total += e.mu * (lower_bound(e.v->begin(), e.v->end(), mid) - e.v->begin());
            }
            if(total < 1) lo = mid;
            else hi = mid;
        }

        low[i] = lo;
    }

    return low;

}

vector<int> lowest() {
    vector<vector<int>*> color_sum(BOUND, nullptr);
    vector<vector<Entry>> out(BOUND);

    int index = 0;
    for(int m : squarefree) {
        vector<int> &ds = das[index];
        // for(int d = m; d < BOUND; d += m) if(exists[d]) ds.push_back(d);
        index++;

        for(int d : ds) {
            // if(color_sum[color(d)] == nullptr || !color_sum[color(d)]->empty())
            // color_sum[color(d)] = new vector<int>{-1};
            color_sum[color(d)] = new vector<int>();
        }

        /*
        for(int d : ds) {
            if(color_sum[color(d)]->size() > 0) color_sum[color(d)]->pop_back();
        } 
        */

        vector<int>* total = new vector<int>();
        for(int d : ds) {
            /*
            total->push_back(d/m);
            color_sum[color(d)]->push_back(d/m);
            */
            total->push_back(d);
            color_sum[color(d)]->push_back(d);
        }

        for(int d : ds) {
            /*
            out[d].push_back({m, mu[m], total});
            out[d].push_back({m, -mu[m], color_sum[color(d)]});
            */
            out[d].push_back({mu[m], total});
            out[d].push_back({-mu[m], color_sum[color(d)]});
        }
    }

    return do_stuff(out);

    // cerr << "up" << endl;
}

bool step() {
    vector<int> low = lowest();

    bool changed = false;
    for(int i = 0; i < BOUND; ++i) if(exists[i] && low[i] < BOUND - 1) {
        // cerr << i << " " << low[i] << endl;
        if(merge(i, low[i])) changed = true;
    }

    return changed;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    init();    
    int num_primes = 0;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        // cerr << a << " - " << radical[a] << endl;
        exists[radical[a]] = true;
        amount[radical[a]]++;
        if(primes[radical[a]] == 1 && amount[radical[a]] == 1) num_primes++;
    }

    if(num_primes > 6) {
        cout << 1 << endl;
        return 0;
    }

    for(int m : squarefree) {
        das.emplace_back();
        for(int d = m; d < BOUND; d += m) if(exists[d]) das.back().push_back(d);
    }

    while(step()) {
        // cerr << "la" << endl;
    }

    unordered_map<int, int> colors;
    for(int i = 0; i < BOUND; ++i) if(exists[i]) colors[color(i)] += 1;
    
    int total = colors.size();
    for(int i = 0; i < BOUND; ++i) if(exists[i] && colors[color(i)] == 1) total += amount[i] - 1;
    cout << total << endl;
}
