#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll pow2(ll e) {
    if(e == 0) return 1;
    ll rec = pow2(e / 2);
    return rec * rec * (e % 2 + 1);
}

int main() {
    ll n, a, b;
    cin >> n >> a >> b;

    struct Creature {
        ll health;
        ll damage;
    };

    vector<Creature> ns(n);
    for(int i = 0; i < n; ++i) {
        ll health, damage;
        cin >> health >> damage;
        ns[i].health = health;
        ns[i].damage = damage;
    }

    if(b == 0) {
        //
        // TODO: special case!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //
    }

    ll delta_last_b = 0;

    if(b < n) {
        if(ns[b - 1].health > ns[b - 1].damage) {
            delta_last_b = ns[b - 1].health - ns[b - 1].damage;
        }
    }

    sort(ns.begin(), ns.end(), [&](Creature a, Creature b) {
            return (a.health - a.damage) < (b.health - b.damage);
            });

    ll p = pow2(a);

    auto delta_if_ith = [&](ll i) -> ll {
        if(ns[i].health * p < ns[i].damage) return 0;
        if(i < b) {
            ll prv = max(0ll, ns[i].health - ns[i].damage);
            ll now = ns[i].health * p - ns[i].damage;

            return now - prv;
        } else {
            return ns[i].health * p - ns[i].damage - delta_last_b;
        }
    };

    ll curr_max = 0;
    for(int i = 0; i < n; ++i) {
        if(delta_if_ith(curr_max) < delta_if_ith(i)) curr_max = i;
    }

    ll total = 0;
    for(int i = 0; i < n; ++i) {
        if(i < b) {
            total += max(ns[i].health, ns[i].damage);
        } else {
            total += ns[i].damage;
        }
    }

    cout << total + delta_if_ith(curr_max) << endl;
}
