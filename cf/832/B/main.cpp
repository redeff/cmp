#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7

template <typename T>
void get_vector(ll size){
  vector<T> out;
  forn(sahdfjhfsk, 0, size){
    T temp;
    cin >> temp;
    out.push_back(temp);
  }
  return out;
}

bool matchstr(char* p, char* m, int len, unordered_set<char> &gut){
  bool is_match = true;
  forn(i, 0, len){
    is_match = is_match && (p[i] == m[i] || (p[i] == '?' && gut.count(m[i]) > 0));
  }
  return is_match;
}

unordered_set<char> gut;

bool matchstr(char* p, char* m, ll len){
  forn(i, 0, len){

    //If the characters are the same
    if(p[i] == m[i]) continue;

    //If they are different and the pattern isn't a '?'
    if(p[i] != '?') return false;

    //If m[i] isn't good
    if(gut.count(m[i]) == 0) return false;
  }

  //All have matched
  return true;
}

int main(){
  {
    string g;
    cin >> g;
    for(char c : g){
      gut.insert(c);
    }
  }
  string pat;
  cin >> pat;

  //Get the index of the asterisk
  ll asterisk = find(pat.begin(), pat.end(), '*') - pat.begin();

  forn(i, 0, n){
    string match;
    cin >> match;

    //Doesn't have an asterisk
    if(asterisk == pat.size()){
      if(pat.size() != match.size()){
        cout << "NO\n";
      } else if(matchstr(&pat[0], &match[0], pat.size())){
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    } else {
      bool matches


int main(){
  string g;
  cin >> g;
  unordered_set<char> gut;
  for(char c : g){
    gut.insert(c);
  }

  string pat;
  cin >> pat;
  ll as = find(pat.begin(), pat.end(), '*') - pat.begin();
  ll n;
  cin >> n;
  forn(i, 0, n){
    string s;
    cin >> s;
    if(as == pat.size()){
      cout << ((pat.size() == s.size() && matchstr(&pat[0], &s[0], pat.size(), gut)) ? "YES" : "NO") << endl;
    } else {
      bool is_match = s.size() >= pat.size() - 1;
      if(is_match){
        ll sl = as + s.size() - pat.size() + 1;
        is_match = is_match && matchstr(&pat[0], &s[0], as, gut);
        is_match = is_match && matchstr(&pat[0] + as + 1, &s[0] + sl, pat.size() - as - 1, gut);
        forn(i, as + 1, sl){
          is_match = is_match && gut.count(s[i]) == 0;
        }
      }
      cout << (is_match ? "YES" : "NO") << endl;
    }
  }
}
