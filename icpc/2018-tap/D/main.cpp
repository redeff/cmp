#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	// Para toda configuración, hay al menos m con menos
	// de k puntos,
	// osea hay a lo sumo n-m con >= a k puntos,
	// osea no puede haber n-m+1 con >= a k puntos.
	//
	// La cantidad de puntos en la óptima va a ser
	// (n-m+1)-1 + 2 * (n - (n-m+1)) = n-m +2(m-1) =
	// n+m-2 < k, luego k = n+m-1
	
	cout << setprecision(1) << fixed;
	cout << (n+m-1) / 2.0 << endl;
}
