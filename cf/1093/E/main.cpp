#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll MAXN = 1000000;
const ll MAXM = 1000000;

struct pairhash {
public:
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const
  {
    return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  }
};

unordered_map<pair<ll, ll>, ll, pairhash> FT;

// Devuelve la suma de A[1..a][1..b]
int getFT (int a, int b){
    a += 3; b += 3;
    int v = 0;
    for (int x = a; x; x -= x & -x)
        for (int y = b; y; y -= y & -y)
            v += FT[{x, y}];
    return v;
}

// Realiza A[a][b] += v
void setFT (int a, int b, int v){
    a += 3; b += 3;
    for (int x = a; x < MAXN; x += x & -x)
        for (int y = b; y < MAXM; y += y & -y)
            FT[{x, y}] += v;
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<int> ns(n, 0);
    for(int i = 0; i < n; ++i){
        cin >> ns[i];
        ns[i]--;
    }


    vector<int> ms(n, 0);
    for(int i = 0; i < n; ++i){ cin >> ms[i]; ms[i]--; }

    vector<int> inv_ms(n, 0);
    for(int i = 0; i < n; ++i) inv_ms[ms[i]] = i;

    vector<int> tot(n, 0);
    for(int i = 0; i < n; ++i) {
        tot[i] = inv_ms[ns[i]];
        setFT(i, tot[i], 1);
    }

    for(int q = 0; q < m; ++q) {
        int typ = 0;
        cin >> typ;
        if(typ == 1) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            a--; b--; c--; d--;
            int total = getFT(b, d) - getFT(b, c - 1) - getFT(a - 1, d) + getFT(a-1, c-1);
            cout << total << endl;
        } else {
            int x, y;
            cin >> x >> y;
            x--; y--;

            for(int i : ms) cout << i << " ";
            cout << endl;

            for(int i : inv_ms) cout << i << " ";
            cout << endl;

            int a = ms[x];
            int b = ms[y];
            setFT(x, inv_ms[ns[x]], -1);
            setFT(y, inv_ms[ns[y]], -1);
            swap(inv_ms[a], inv_ms[b]);
            swap(ms[x], ms[y]);
            setFT(x, inv_ms[ns[x]], 1);
            setFT(y, inv_ms[ns[y]], 1);

            for(int i : ms) cout << i << " ";
            cout << endl;

            for(int i : inv_ms) cout << i << " ";
            cout << endl;

        }
    }

}
