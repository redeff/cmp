#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
    ll n;
    cin >> n;
    vector<ll> cs;
    for(int i = 0; i < n; ++i) {
        ll tmp;
        cin >> tmp;
        cs.push_back(tmp);
    }

    sort(cs.begin(), cs.end());
    ll median = cs[n/2];
    median /= 2;

    // ll siz = max(100ll, n + 2);
    ll a = max(50ll, (n + 1) / 2);
    ll b = max(50ll, (n + 2) / 2);

    unordered_set<int> as;
    unordered_set<int> bs;


    ll loa = median + 1 - a22;
    ll hia = median + a - a/2;
    if(loa < 1) {
        hia += 1 - loa;
        loa = 1;
    }
    if(hia > 5000) {
        loa -= hia - 5000;
        hia = 5000;
    }

    for(int i = loa; i <= hia; ++i) {
        as.insert(i);
    }

    ll lob = median + 1 - b/2;
    ll hib = median + b - b/2;
    if(lob < 1) {
        hib += 1 - lob;
        lob = 1;
    }
    if(hib > 5000) {
        lob -= hib - 5000;
        hib = 5000;
    }

    for(int i = lob; i <= hib; ++i) {
        bs.insert(i);
    }

    /*
    for(int i = median - a/2; i < median + a - a/2; ++i) {
        
    }
    */

    /*
    for(int i = 1; i <= max(50ll, siz/2); ++i) {
        if(0 < i + mid && i + mid <= 5000)
            bs.insert(i + mid);
    }

    if(bs.size() < max(50ll, siz/2)) {
        bs.clear();
        for(int i = 1; i <= max(50ll, siz/2); ++i) {
            if(i <= 5000)
                bs.insert(i);
        }
    }
    */

    cout << as.size() << endl;
    for(auto a : as) cout << a << " ";
    cout << endl;

    cout << bs.size() << endl;
    for(auto b : bs) cout << b << " ";
    cout << endl;

    /*
    cout << min(siz / 2, 5000ll) << endl;
    // cout << 5000 << endl;
    for(int i = 1; i <= 5000; ++i) {
        cout << i << endl; 
    }

    // cout << min(siz / 2, 5000ll) << endl;
    cout << 5000 << endl;
    for(int i = 1; i <= 5000; ++i) {
        cout << i << endl; 
    }
    */
}
