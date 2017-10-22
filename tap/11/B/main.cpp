#include <bits/stdc++.h>
using namespace std;

int main(){
  while(true){
    string S;
    string T;
    cin >> S;
    cin >> T;
    if(S == "*") break;
    vector<bool> s {false};
    vector<bool> t {false};

    for(int i = 0; i < S.size(); ++i){
      s.push_back(S[i] == 'B');
      t.push_back(T[i] == 'B');
    }

    s.push_back(false);
    t.push_back(false);

    int total = 0;
    for(int i = 1; i < s.size(); ++i){
      if((s[i] == t[i]) != (s[i - 1] == t[i - 1])){
        total++;
      }
    }
    cout << total / 2 << endl;
  }
}
