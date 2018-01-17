#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < int(n); ++i)
using namespace std;

// Si se puede con suma maxima de paginas d, entonces
// construye la particion optima con respecto al problema
vector<vector<int>> get_partition(vector<int> arr, int d, int k, int m) {
  int taken = 0;
  vector<vector<int>> all;
  forn(i, k) {
    all.emplace_back();
    int curr = 0;

    // Hacemos greedy del lado opuesto (el array lo
    // invertimos al principio de testcase), cosa de que
    // en vez de minimizar la cantidad de paginas del
    // primer escriba, queramos minimizar las del ultimo,
    // por lo que combiene tomar todas las posibles al principio
    //
    // La cota i - k + m es para que siempre queda al menos un libro
    // para los escribas restantes
    while(taken <= i - k + m && curr <= d) {
      curr += arr[taken];
      all.back().emplace_back(arr[taken]);
      taken++;
    }
    if(curr > d) {
      taken--;
      curr -= arr[taken];
      all.back().pop_back();
    }
  }
  return all;
}

// Casi lo mismo que la otra funcion, pero en vez de contruir
// el ejemplo, chequea si se puede con d
bool is_possible(vector<int> arr, int d, int k, int m) {
  int taken = 0;
  forn(i, k) {
    int curr = 0;
    while(taken <= i - k + m && curr <= d) {
      curr += arr[taken];
      taken++;
    }
    if(curr > d) {
      taken--;
      curr -= arr[taken];
    }
  }
  return taken == m; 
}

void testcase() {
  int m, k;
  cin >> m >> k;

  int sum = 0;
  vector<int> ps;
  forn(i, m) {
    ps.emplace_back();
    cin >> ps.back();
    sum += ps.back();
  }

  reverse(ps.begin(), ps.end());

  // Hacemos busqueda binaria. Con d = sum siempre se puede
  // (le damos todo a un escriba), y con d = 0 obvio que no
  int lo = 0;
  int hi = sum; // Can

  while(lo != hi - 1) {
    int mid = (lo + hi) / 2;
    if(is_possible(ps, mid, k, m)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  auto res = get_partition(ps, hi, k, m);

  // Invertimos de nuevo (porque lo habíamos invertido antes)
  reverse(res.begin(), res.end());
  forn(i, res.size()) {
    reverse(res[i].begin(), res[i].end());
    forn(j, res[i].size()) {
      cout << res[i][j];
      if(!(i == int(res.size()) - 1 && j == int(res[i].size()) - 1)) {
        cout << " ";
      }
    }
    if(i != int(res.size()) - 1)
      cout << "/ ";
  }
  cout << endl;
}

/*

  int lo = 0;
  int hi = sum;

  while(lo != hi - 1) {
    int mid = (lo + hi) / 2;

    int book_index = 0;
    bool works = false;
    forn(i, k) if(!works){
      int this_scribe = 0;
      while(this_scribe < mid && book_index < i + m - k + 1 && !works) {
        if(book_index >= m) {
          works = true;
          break;
        }
        this_scribe += ps[book_index];
        book_index++;
      }
      book_index--;
    }

    if(works) hi = mid; else lo = mid;
  }

  int book_index = 0;
  vector<vector<int>> all;
  forn(i, k) {
    int this_scribe = 0;
    vector<int> these_books;
    while(this_scribe < lo && book_index < i + m - k + 1) {
      this_scribe += ps[book_index];
      these_books.push_back(ps[book_index]);
      book_index++;
    }
    if(this_scribe > lo) {
      book_index--;
      these_books.pop_back();
    }
    all.push_back(these_books);
    //for(auto b : these_books) {
    //  cout << b << " ";
    //}

    // if(i != k - 1) cout << "/ ";
  }

  // cout << lo << endl;
  for(int i = k - 1; i >= 0; --i) {
    reverse(all[i].begin(), all[i].end());
    forn(j, all[i].size()) {
      cout << all[i][j];
      if(i != 0 || j != all[i].size() - 1) cout << " ";
    }
    if(i != 0) cout << "/ ";
  }
  cout << endl;
*/
//}

int main() {
  int T;
  cin >> T;
  forn(i, T) testcase();
}
