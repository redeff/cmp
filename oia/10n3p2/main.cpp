#include <bits/stdc++.h>
using namespace std;

void get_virus(vector<int> per, int m, int offset, vector<int> &out) {
  //cout << "vir" << endl;
  for(auto p : per){
    //cout << p << endl;
  }
  if(per.size() < m) return;
  vector<int> amounts(m, 0);
  unordered_set<int> nonones;
  for(int i = 0; i < m; ++i) nonones.insert(i);
  for(int i = 0; i < m; ++i){
    int p = per[i]; 
    amounts[p]++;
    if(amounts[p] == 1){
      nonones.erase(p);
    } else if (amounts[p] == 2) {
      nonones.insert(p);
    }
  }

  if(nonones.empty()){
    out.push_back(offset);
  }

  //cout << "where"<< endl;

  for(int i = 0; i < per.size() - m; ++i) {
    int p = per[i]; 
    int pm = per[i + m]; 
    amounts[p]--;
    amounts[pm]++;
    if(amounts[p] == 1){
      nonones.erase(p);
    } else /*if (amounts[p] == 0)*/ {
      nonones.insert(p);
    }
    if(amounts[pm] == 1){
      nonones.erase(pm);
    } else /*if (amounts[pm] == 2)*/ {
      nonones.insert(pm);
    }
    if(nonones.empty()){
      out.push_back(offset + i + 1);
    }
  }
} 

#define cout out
#define cin ini

int main() {
  ofstream out;
  out.open("polimorfo.out");
  ifstream ini;
  ini.open("polimorfo.in");
  int n, m;
  cin >> n >> m;
  vector<int> ins(n);
  for(int i = 0; i < n; ++i){
    cin >> ins[i];
    ins[i]--;
  }

  vector<int> curr;
  vector<int> total;
  for(int i = 0; i <= n; ++i){
    //cout << "tadaa " << i << endl;
    if(i == n || ins[i] >= m || ins[i] < 0){
      //cout << "tudaa " << i << endl;
      get_virus(curr, m, i - curr.size(), total);
      curr = vector<int>();
    } else {
      curr.push_back(ins[i]);
    }
  }

  /*for(auto t : total){
    cout << "is: " << t + 1 << endl;
  }*/
  cout << total.size() << endl;
  if(total.size() < 10){
    for(auto t : total) cout << t + 1 << " ";
  } else {
    for(int i = 0; i < 5; ++i){
      cout << total[i] + 1 << " ";
    }

    for(int i = total.size() - 5; i < total.size(); ++i){
      cout << total[i] + 1 << " ";
    }
  }
  cout << endl;
}
