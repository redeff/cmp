#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define forn(i, a, b) for(ll i = a; i < b; ++i)
ll MOD = 1000000007; //10^9 + 7

template <typename T>
vector<T> get_vector(ll size) {
  vector<T> out;
  forn(sahdfjhfsk, 0, size)
  {
    T temp;
    cin >> temp;
    out.push_back(temp);
  }
  return out;
}

multiset<ll> binary(long long unsigned int n)
{
  multiset<ll> out;
  for(long long unsigned int i = 0ull; i < 64ull; ++i)
  {
    if((1ull << i) & n)
    {
      out.insert(i);
    }
  }
  return out;
}

int main()
{
  ll k;
  long long unsigned int n;
  cin >> n >> k;

  auto bin = binary(n);
  if(bin.size() > k)
  {
    cout << "No" << endl;
    return 0;
  }

  while(bin.size() < k)
  {
    ll largest = *bin.rbegin();
    bin.insert(largest-1);
    bin.insert(largest-1);
    bin.erase(prev(bin.end()));
    // -
  }
  int snds = bin.count(*bin.rbegin() - 1);
  bin.erase(*bin.rbegin() - 1);
  if(snds % 2 == 1)
  {
    bin.insert(*bin.rbegin() - 1);
  }
  forn(i, 0, snds / 2) bin.insert(*bin.rbegin());

  while(bin.size() < k)
  {
    auto les = bin.begin();
    auto val = *les - 1;
    bin.erase(les);
    bin.insert(val);
    bin.insert(val);
  }

  cout << "Yes" << endl;
  for(auto p = bin.rbegin(); p != bin.rend(); ++p)
  {
    cout << *p << " ";
  }
  cout << endl;
}
