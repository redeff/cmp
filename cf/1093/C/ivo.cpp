#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
    int n;
    cin >> n;
    
    vector<ll> ns(n, 0);
    for(int i = 0; i < n/2; ++i) {
        cin >> ns[i];
    }

    for(int i = 0; i < n/2; ++i) {
        int other = n - i - 1;
        if(i == 0) {
            ns[other] = ns[i];
            ns[i] = 0;
        } else {
            int total = ns[i];
            ns[other] = ns[other + 1];
            ns[i] = total - ns[other];
   if(ns[i] >= ns[i-1] && ns[other+1] >= ns[other]){
    
   }
   else{
    ns[i] = ns[i-1];
             ns[other] = total - ns[i];
   }
            
        }
    }

    for(ll t : ns) cout << t << " ";
    cout << endl;
}
