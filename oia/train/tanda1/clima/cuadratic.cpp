
int main(){
  ifstream ifs;
  ifs.open("clima.in");
  ofstream ofs;
  ofs.open("clima.out");

  int n;
  ifs >> n;

  vector<Estacion> es;

  for(int i = 0; i < n; ++i) {
    int p = 33333333; // Minima
    int q = -33333333; // Maxima
    int r;
    ifs >> r;
    for(int j = 0; j < r; ++j) {
      int pl, ql;
      ifs >> pl >> ql;
      p = min(p, pl);
      q = max(q, ql);
    }

    es.emplace_back(-p, q);
  }

  vector<pair<int, int>> d(n, make_pair(0, 0));
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      if(

}


