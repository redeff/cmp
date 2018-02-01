#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

// No hacemos DP, ya que calc tiene suficientemente buena complejidad,
// es sublineal

ll calc(ll t) {
    if(t == 1) return 0;
    if(t == 2) return 1;
    // Notmeos que nunca combiene hacer -1 -> -1 -> /2, 
    // ya que podríamos haber hecho     /2 -> -1
    // y tiene el mismo efecto y es mas corto
    //
    // Similarmente no combiene hacer   -1 -> -1 -> -1 -> /3
    // Ya que más vale hacer            /3 -> -1
    //
    // Entonces hay solo dos posibilidades, si querés hacer
    // /2 sacás exactamente la cantidad de 1s necesaria (si es impar
    // una vez, si es par 0 veces)
    // y si querés hacer /3 podés tener que sacas 1 hasta 2 veces,
    // dependiendo del valor de n % 3
    //
    // el +1 está porque la división en sí cuesta
    return min(calc(t / 2) + t % 2 + 1, calc(t / 3) + t % 3 + 1);

    // Creo que esto tiene complejiad n^a, donde a es tal que:
    //
    //       1 / (2^a) + 1 / (3^a) == 1   <=>   2^a + 3^a == 6^a,
    //
    // pero no se calcular ese a
    //
    // Geogebra confirma que este a (que me da ~0.78788) cumple:
    // si f(x) = x^a entonces f(x) = f(x/2) + f(x/3), entonces
    // x^a cumple con la cota de complejidad
    //
    // No se si este análisis está bien, a lo mejor me pueden decir
}

int main() {
    ll t;
    cin >> t;
    for(ll i = 0; i < t; ++i) {
        ll n;
        cin >> n;
        cout << "Case " << i + 1 << ": " << calc(n) << endl;
    }
}
