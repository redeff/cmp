#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7

struct Node {
  ll parent = -1;
  ll depth = -1;
};

ll dist(ll a, ll b, vector<Node> &nodes){
  if(nodes[a].depth < nodes[b].depth)return 1 + dist(a, nodes[b].parent, nodes);
  if(nodes[a].depth > nodes[b].depth)return 1 + dist(nodes[a].parent, b, nodes);
  if(a == b)return 0;
  return 2 + dist(nodes[a].parent, nodes[b].parent, nodes);
}
  

template <typename T>
vector<T> get_vector(ll size){
  vector<T> out;
  forn(sahdfjhfsk, 0, size){
    T temp;
    cin >> temp;
    out.push_back(temp);
  }
  return out;
}

void fillup(ll d, ll i, vector<vector<ll>> &conn, vector<Node> &nodes){
  nodes[i].depth = d;
  for(ll c : conn[i]) if(c != nodes[i].parent){
    nodes[c].parent = i;
    fillup(d + 1, c, conn, nodes);
  }
}

int main(){
  ll n, q;
  cin >> n >> q;
  vector<vector<ll>> conn(n);
  vector<Node> nodes(n);
  forn(i, 1, n){
    ll a;
    cin >> a;
    a--;
    conn[a].push_back(i);
    conn[i].push_back(a);
  }

  fillup(0, 0, conn, nodes);
  forn(i, 0, q){
    ll a, b, c;
    cin >> a >> b >> c;
    a--; b--; c--;
    ll p, q, r;
    p = dist(a, b, nodes);
    q = dist(c, b, nodes);
    r = dist(a, c, nodes);
    cout << max((p + q - r) / 2, max((p + r - q) / 2, (q + r - p) / 2)) + 1 << endl;
  }


}
