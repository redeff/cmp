#include <bits/stdc++.h>
using namespace std;

const int EXP = 18;
const int BOUND = 1 << EXP;


int mobius[BOUND];
int radical[BOUND];
int color[BOUND];
int sum_over_color[BOUND];

int bin[EXP][BOUND];
int exists[BOUND];
int low[BOUND];
int amount[BOUND];
bool colored[BOUND];

/*
vector<int> mobius;
vector<int> radical;
vector<int> color;
vector<int> sum_over_color;

vector<vector<int>> bin;
vector<int> exists;
vector<int> low;
*/

vector<int> squarefree;

void init() {
    /*
    mobius = vector<int>(BOUND, 1);
    radical = vector<int>(BOUND, 1);
    color = vector<int>(BOUND);
    sum_over_color = vector<int>(BOUND);
    exists = vector<int>(BOUND, 0);
    bin = vector<vector<int>>(EXP, vector<int>(BOUND));
    low = vector<int>(BOUND);
    */
    for(int i = 0; i < BOUND; ++i) {
        mobius[i] = 1;
        radical[i] = 1;
        color[i] = i;
        sum_over_color[i] = 0;
        exists[i] = 0;
        amount[i] = 0;
    }

    for(int i = 2; i < BOUND; ++i) {
        if(mobius[i] == 1) {
            for(int j = i; j < BOUND; j += i) {
                mobius[j] *= -i;
                radical[j] *= i;
            }

            if(i <= BOUND/i) for(int j = i * i; j < BOUND; j += i * i) {
                mobius[j] = 0;
            }
        } 
    }

    for(int i = 2; i < BOUND; ++i) {
        if(mobius[i] == 0) {}
        else if(mobius[i] == i) mobius[i] = 1;
        else if(mobius[i] == -i) mobius[i] = -1;
    }

    for(int i = 1; i < BOUND; ++i) if(mobius[i] != 0) squarefree.push_back(i);
}

/*
void init_colors() {
    for(int i = 0; i < BOUND; ++i) {
        colors[i] = i;
        color_util[i] = 0;
    }
}
*/

void degrees() {
    for(int e = 0; e < EXP; ++e) {
        for(int i = 0; i < BOUND; ++i) bin[e][i] = 0;
        // for(int m = 1; m < BOUND; ++m) if(mobius[m] != 0) {
        for(int m : squarefree) {
            // m is squarefree

            vector<int> ts;
            for(int t = m; t < BOUND; t += m) if(exists[t]) ts.push_back(t);
            for(int t : ts) {
            // for(int t = m; t < BOUND; t += m) {
                sum_over_color[color[t]] = 0;
            }
            int total = 0;

            for(int t : ts) {
            // for(int t = m; t < BOUND; t += m) {
                int d = exists[t] * ((t & (1 << EXP)) == 0);
                total += d;
                sum_over_color[color[t]] += d;
            }

            for(int t : ts) {
            // for(int t = m; t < BOUND; t += m) {
                bin[e][t] += mobius[m] * (total - sum_over_color[color[t]]);
            }
        }
    }
}

void lowest_connection() {
    degrees();
    for(int i = 0; i < BOUND; ++i) {
        low[i] = 0;
        for(int e = 0; e < EXP; ++e) {
            if(bin[e][i] == 0) {
                low[i] += 1 << e; 
            }
        }
    }
}

void colorize(int k) {
    if(colored[k] || low[k] == BOUND - 1) return;
    else {
        colorize(
        
    }
}

int main() {
    init();
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        // exists[radical[a]] = 1;
        exists[radical[a]] = 1;
        amount[radical[a]] += 1;
        // cerr << a << " " << radical[a] << endl;
    }
    // cerr << "Init done" << endl;

    bool changed = true;
    while(changed) {
        changed = false;
        lowest_connection();
        for(int i = 0; i < BOUND; ++i) colored[i] = false;
        for(int i = 0; i < BOUND; ++i) {
            if(low[i] < i && color[i] != color[low[i]]) {
                changed = true;
                color[i] = color[low[i]];
            }
        }
        // cerr << "Loop done" << endl;
    }

    // cerr << "Almost" << endl;
    unordered_map<int, int> colors;
    for(int i = 0; i < BOUND; ++i) if(exists[i]) colors[color[i]] += 1;
    
    int total = colors.size();
    for(int i = 0; i < BOUND; ++i) if(exists[i] && colors[color[i]] == 1) total += amount[i] - 1;
    cout << total << endl;
}
