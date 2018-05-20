#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll pow2(ll e) {
    if(e == 0) return 1;
    ll rec = pow2(e / 2);
    return rec * rec * (e % 2 + 1);
}

struct Creature {
    ll health;
    ll damage;
};

ll without_a(ll b, vector<Creature> ns) {
    /*
    sort(ns.begin(), ns.end(), [&](Creature a, Creature b) {
            return (a.health - a.damage) > (b.health - b.damage);
            });
    */

    ll total = 0;
    for(int i = 0; i < ns.size(); ++i) {
        if(i < b) {
            total += max(ns[i].health, ns[i].damage);
        } else {
            total += ns[i].damage;
        }
    }
    return total;
}

int main() {
    ll n, a, b;
    cin >> n >> a >> b;

    vector<Creature> ns(n);
    for(int i = 0; i < n; ++i) {
        ll health, damage;
        cin >> health >> damage;
        ns[i].health = health;
        ns[i].damage = damage;
    }

    sort(ns.begin(), ns.end(), [&](Creature a, Creature b) {
            return (a.health - a.damage) > (b.health - b.damage);
            });

    ll p = pow2(a);
    if(b == 0) {
        cout << without_a(b, ns) << endl;
        return 0;
    }

    auto delta = [&](ll i) {
        ll now = max(ns[i].health * p - ns[i].damage, 0ll);
        ll prv = i < b ? max(ns[i].health - ns[i].damage, 0ll) : 0;
        return now - prv;
    };

    ll option_1 = 0;
    for(int i = 0; i < min(n, b); ++i) {
        if(delta(option_1) < delta(i)) option_1 = i;
    }

    ns[option_1].health *= p;
    ll best = without_a(b, ns);
    ns[option_1].health /= p;

    if(b < n) {
        ll option_2 = n - 1;
        for(int i = min(n, b); i < n; ++i) {
            if(delta(option_2) < delta(i)) option_2 = i;
        }

        ns[option_2].health *= p;
        best = max(best, without_a(b, ns));
        ns[option_2].health /= p;
    }

    cout << best << endl;

    /*
    ll without_a = 0;
    for(int i = 0; i < n; ++i) {
        if(i < b) {
            without_a += max(ns[i].health, ns[i].damage);
        } else {
            without_a += ns[i].damage;
        }
    }
    */

}
