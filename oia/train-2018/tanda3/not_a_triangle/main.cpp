#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)

void testcase(int n) {
  vector<int> ns;
  forn(i, n) {
    ns.emplace_back();
    cin >> ns.back();
  }

  sort(ns.begin(), ns.end());

  int total = 0;
  vector<int> iot;
  forn(i, n) iot.push_back(i);
  forn(i, n) forn(j, i) {
    // Queremos todos los pares (i, j, k) tal que ns[i] ns[j] ns[k] no formen un triangulo,
    // y le daremos el orden erbitrario i > j > k => ns[i] >= ns[j] >= ns[k]
    // Para que no se forme un triangulo, ns[k] < ns[i] - ns[j]
    // Juntando las condiciones ns[k] < ns[i] - ns[j] y k < j, que particionan [0;n),
    // podemos usar binary search para saber cuantos tales k hay
    //
    // iot es [0;n)
    total += int(lower_bound(iot.begin(), iot.end(), ns[i] - ns[j], [&](int index, int val) { // (Index es k)
        return ns[index] < val && index < j;
    }) - iot.begin());
  }

  cout << total << endl;
}

int main() {
  int t;
  while(true) {
    cin >> t;
    if(t == 0) break;
    testcase(t);
  }
}
