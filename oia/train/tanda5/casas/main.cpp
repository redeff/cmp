#include <bits/stdc++.h>
using namespace std;

const int INF = 33333333;

// #define LOCAL

#ifndef LOCAL
#define ifs cin
#define ofs cout
#endif //LOCAL

int main() {
#ifndef LOCAL
    ifstream ifs("casas.in");
    ofstream ofs("casas.out");
#endif //LOCAL

    int x, y;
    cin >> x >> y;
    int c;
    cin >> c;

    vector<int> cs(c);
    for(int i = 0; i < c; ++i) {
        cin >> cs[i];
    }

    int size = x / 2;

    struct Entry {
        int area;
        int from;
        int size;
        Entry(int area_, int from_, int size_): area(area_), from(from_), size(size_) {}
        Entry(){}
    };

    // La idea es hacer dinámica. Para cada tamaño posible de cada casa, evaluamos
    // cual es la cantidad máxima de area que podría tener todas las casas anteriores juntas,
    // además guardamos, para ese máximo, el tamaño de la casa anterior, así podemos cuando
    // terminamos ir yendo para atrás y averiguar el tamaño de cada casa para lograr el máximo

    // Para cada casa y para cada tamaño
    vector<vector<Entry>> dp(c, vector<Entry>(size, Entry(-INF, -1, -1)));

    // Los casos base para la primer casa
    for(int i = 0; i < cs[0]; ++i) {
        int dist = cs[0] - i;
        if(dist <= size && dist + cs[0] <= y) {
            dp[0][dist - 1].area = dist * dist * 4; 
            dp[0][dist - 1].size = dist; 
        }
    }

    for(int i = 1; i < c; ++i) {
        // Tenemos que tener en cuenta que a lo mejor lo óptimo requere que haya gaps entre las casas
        // Por eso dado el tamaño de una casa, tenemos tque fijarnos TODOS los tamaños posibles
        // de la casa anterior que no se superponen con la actual. Eso es lo que guarda max_area
        int max_area = -INF;
        int from = -1;
        for(int j = cs[i - 1] + 1; j < cs[i]; ++j) {
            // j es una división que se va moviendo entre dos posiciones sucesivas de fuente de entergia

            //Tomamos la distancia a la fuente anterior y siguiente
            int dist_to_prev = j - cs[i - 1];
            int dist_to_next = cs[i] - j;

            // si podemos poner una casa en la fuente anterior suficientemente grande para que toque la división ...
            if(dist_to_prev <= size) {
                int this_area = dp[i - 1][dist_to_prev - 1].area;

                // ... hacemos que max_area se actualice si para ese tamaño hay un sifijo más
                // optimo de tamaños de casas. Además actualizamos from para saber de que tamaño
                // vino en mayor hasta ahora
                if(this_area > max_area) {
                    max_area = this_area;
                    from = dist_to_prev - 1;
                }
                // max_area = max(max_area, dp[i - 1][dist_to_prev - 1].area);
            }

            // si podemos poner una casa en la fuente siguiente suficientemente grande para que toque la división ...
            if(dist_to_next <= size && cs[i] + dist_to_next <= y) {

                // Ya sabemos el óptimo de todos los sufijos de tamaños de casas tales que todas estén antes
                // de la división j, y cual el el tamaño de la casa anterior correspondiente, así que usamos esta info:
                dp[i][dist_to_next - 1].area = max_area + 4 * dist_to_next * dist_to_next;
                dp[i][dist_to_next - 1].size = dist_to_next;
                dp[i][dist_to_next - 1].from = from;
            }
        }
    }

    Entry mx(-INF, -1, -1);
    for(int i = 0; i < size; ++i) {
        if(dp.back()[i].area > mx.area) {
            mx = dp.back()[i];
        }
    }

    cout << mx.area << endl;

    vector<int> houses;

    // Vamos yendo para atrás como dijimos
    for(int i = c - 1; i >= 0; --i) {
        houses.push_back(mx.size);
        if(mx.from == -1) break;
        else mx = dp[i - 1][mx.from];
    }

    reverse(houses.begin(), houses.end());

    // 2* porque guardamos el radio de la casa en realidad, no su tamaño
    for(auto h : houses) cout << 2*h << endl;
}
