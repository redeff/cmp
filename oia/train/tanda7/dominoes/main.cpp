#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct Domino {
    ll start;
    ll end;

    Domino(ll start, ll end) : start(start), end(end) {}
    Domino() : start(-1), end(-1) {}
};

int main() {
    int n;
    cin >> n;
    vector<Domino> ns(n);

    for(int i = 0; i < n; ++i) {
        ll p, l;
        cin >> p >> l;
        ns[i].start = p;
        ns[i].end = p + l;
        // cin >> ns[i].pos >> ns[i].len;
    }

    struct Entry {
        Domino domino;
        ll spac;
        int index;
    };

    struct Query {
        int start;
        int end;
    };

    ll q;
    cin >> q;
    vector<Query> qs(q);
    for(ll i = 0; i < q; ++i) {
        int s, e;
        cin >> s >> e;
        assert(s != 0 && e != 0);
        qs[i].start = s - 1;
        qs[i].end = e - 1;

        assert(qs[i].start != -1);
        assert(qs[i].end != -1);
    }

    assert(qs[q - 1].end != -1);

    vector<int> iot(q);
    for(int i = 0; i < q; ++i) iot[i] = i;
    sort(iot.begin(), iot.end(), [&](int a, int b) {return qs[a].start < qs[b].start;});

    vector<Query> ordered(q);
    for(int i = 0; i < q; ++i) {
        ordered[i] = qs[iot[i]];
    }
    swap(ordered, qs);
    // sort(qs.begin(), qs.end(), [&](Query q1, Query q2) {return q1.start < q2.start;});

    vector<Entry> joint;
    vector<ll> results;
    for(int i = n - 1; i >= 0; --i) {
        Domino curr = ns[i];
        while(!joint.empty() && joint.back().domino.start <= curr.end) {
            curr.end = max(curr.end, joint.back().domino.end);
            joint.pop_back();
        }

        ll spac;
        if(joint.empty()) {
            spac = 0;
        } else {
            spac = joint.back().spac + joint.back().domino.start - curr.end;
        }
        joint.emplace_back();
        joint.back().spac = spac;
        joint.back().domino = curr;
        joint.back().index = i;

        while(!qs.empty() && qs.back().start == i) {
            Query q = qs.back();
            qs.pop_back();

            int lo = joint.size() - 1;
            int hi = -1;

            while(lo - hi > 1) {
                int mid = (hi + lo) / 2;
                if(joint[mid].index <= q.end) lo = mid;
                else hi = mid;
            }
            // cerr << q.end << " " << joint[lo].index << endl;
            results.push_back(joint.back().spac - joint[lo].spac);
        }

        /*
        cerr << "#" << i << ", ";
        for(Entry e : joint) {
            cerr << e.domino.start << ":" << e.domino.end << " " << e.spac << " " << e.index << " ; ";
        }
        */
        // cerr << endl;
    }

    reverse(results.begin(), results.end());

    vector<ll> real_results(q);
    for(int i = 0; i < q; ++i) {
        real_results[iot[i]] = results[i];
    }

    for(ll r : real_results) {
        cout << r << endl;
    }
}
