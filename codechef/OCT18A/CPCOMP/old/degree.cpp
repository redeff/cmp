#include <bits/stdc++.h>
using namespace std;

const int EXP = 18;
const int BOUND = 1 << EXP;

vector<int> mu;
vector<int> radical;
vector<int> squarefree;
vector<Uf> uf;

vector<bool> exists;

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

    exists = vector<bool>(BOUND, false);
}

vector<int> degrees() {
    vector<int> out(BOUND, 0);

    for(int m : squarefree) {
        vector<int> ds;
        for(int d = m; d < BOUND; d += m) if(exists[d]) ds.push_back(d);

        int total = 0;
        for(int d : ds) {
            int disc = ((d & (1 << e)) == 0) ? 1 : 0;
            total += mu[m] * disc;
        }

        for(int d : ds) {
            out[d] += total;
        }
    }

    return out;
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
    }

    vector<int> deg = degrees();
    for(int d : deg) cout << d << " ";
    cout << endl;
}
