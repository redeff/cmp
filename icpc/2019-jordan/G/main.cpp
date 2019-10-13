#include <bits/stdc++.h>
#define forn(i, z, n) for(int i = z; i < n; ++i)
using namespace std;
typedef long long int ll;
ll inf = 3000000000000000000ll;
ll big = 2000000000000000000ll;

int lp2(int n) {
	int i = 1;
	while(i < n) i*=2;
	return i;
}

/*
pair<ll, int> min(pair<ll, int> a, pair<ll, int> b) {
    if(a.first < b.first) {
        return a;
    } else 
}
*/

struct STree {
        vector<ll> lazy;
        vector<pair<ll, int>> st;
        int n;
        STree(int n): st(4*n+5, make_pair(inf,0)), lazy(4*n+5, 0), n(n) {}
        void init(int k, int s, int e, ll *a, int bound) {
            lazy[k] = 0;
            if(s+1==e){
					if(s < bound) st[k]={a[s],s};
					else st[k] = {inf, 0};
					return;
				}
            int m = (s+e)/2;
            init(2*k,s,m,a,bound);
            init(2*k+1,m,e,a,bound);
            st[k] = min(st[2*k], st[2*k+1]);
        }
        
        void push(int k, int s, int e) {
            st[k].first+=lazy[k];
            if(s+1<e) {
                lazy[2*k]+=lazy[k];
                lazy[2*k+1]+=lazy[k];
            }
            lazy[k] = 0;
        }
        void upd(int k, int s, int e, int a, int b, ll v){
            push(k, s, e);
            if(a==b||s >= b|| e<= a) return;
            if(s >= a && e <= b) {
                lazy[k]+=v;
                push(k,s,e);
                return;
            }
            int m=(s+e)/2;
            upd(2*k,s,m,a,b,v);
            upd(2*k+1,m,e,a,b,v);
            st[k] = min(st[2*k], st[2*k+1]);
        }
        pair<ll, int> query(int k, int s, int e, int a, int b) {
            if(a==b||s>=b || e<=a) return {inf+1,0};
            push(k, s, e);
            if(s >= a && e <= b) return st[k];
            int m = (s+e)/2;
            return min(query(2*k,s,m,a,b),query(2*k+1,m,e,a,b));
        }
        void init(ll *a, int b){init(1,0,n,a,b);}
        void upd(int a, int b, ll v){upd(1,0,n,a,b,v);}
        pair<ll, int> query(int a, int b){return query(1,0,n,a,b);}
};

struct STreeSum {
        vector<int> lazy;
        vector<int> st;
        int n;
        STreeSum(int n): n(n), st(4*n+5, 0), lazy(4*n+5, 0) {}
        void init(int k, int s, int e) {
            lazy[k] = 0;
            if(s+1==e){st[k]=0;return;}
            int m = (s+e)/2;
            init(2*k,s,m);
            init(2*k+1,m,e);
            st[k] = 0;
        }
        
        void push(int k, int s, int e) {
            st[k]+=(e-s)*lazy[k];
            if(s+1<e) {
                lazy[2*k]+=lazy[k];
                lazy[2*k+1]+=lazy[k];
            }
            lazy[k] = 0;
        }
        
        
        void upd(int k, int s, int e, int a, int b, int v){
            push(k, s, e);
            if(a == b || s >= b|| e <= a) return;
            if(s >= a && e <= b) {
                lazy[k]+=v;
                push(k,s,e);
                return;
            }
            int m=(s+e)/2;
            upd(2*k,s,m,a,b,v);
            upd(2*k+1,m,e,a,b,v);
            st[k] = st[2*k] + st[2*k+1];
        }
        int query(int k, int s, int e, int a, int b) {
            if(a==b||s>=b || e<=a) return 0;
            push(k, s, e);
            if(s >= a && e <= b) return st[k];
            int m = (s+e)/2;
            return query(2*k,s,m,a,b) + query(2*k+1,m,e,a,b);
        }
        void init(){init(1,0,n);}
        void upd(int a, int b, int v){upd(1,0,n,a,b,v);}
        int query(int a, int b){return query(1,0,n,a,b);}
};

int main() {
    int n;
    while(cin >> n) {
        vector<ll> as(n);
        vector<ll> bs(n);
        forn(i, 0, n) {
            cin >> as[i] >> bs[i];
        }
        vector<ll> sums = as;
        forn(i, 1, n) {
            sums[i] += sums[i-1];
        }
        forn(i, 0, n) sums[i] += bs[i];
        
        STree rmq(lp2(n));
        rmq.init(&sums[0], n);
        
        STreeSum deadst(lp2(n));
        deadst.init();
        vector<bool> deads(n, false);
        /*
        Stree oth(n);
        for(ll &i : sums) i = i-bs[i];
        oth.init(sums);
        */
        
        auto update = [&](int pos, ll a, ll b) {
            rmq.upd(pos, n, a - as[pos]);
            as[pos] = a;
            rmq.upd(pos, pos+1, b - bs[pos]);
            bs[pos] = b;
        };
        int q;
        cin >> q;
        for(int i = 0; i < q; ++i) {
            int t;
            cin >> t;
            if(t == 1) {
                int lo = -1;
                int hi = n;
                ll x;
                cin >> x;
                while(hi - lo > 1) {
                    int mid = (hi+lo)/2;
                    ll part = rmq.query(mid, mid+1).first - bs[mid];
                    if(part > x) hi = mid;
                    else lo = mid;
                }
                // cerr << "BINSEARCHED" << endl;

                int died = 0;
                vector<int> dead;
                while(true) {
                    pair<ll, int> mn = rmq.query(0, hi);
                    if(x > mn.first) {
                        // cout << x << " " << mn.first << endl;
                        // cout << rmq.query(mn.second, mn.second+1).first << " " << mn.first << " " << mn.second << endl;
                        update(mn.second, as[mn.second], big);
                        dead.push_back(mn.second);
                        // update(mn.second, 0, big);
                        died++;
                    } else break;
                }
                // cerr << "KILLED" << endl;
                for(int d : dead) {
                    assert(!deads[d]);
                    deads[d] = true;
                    deadst.upd(d, d+1, 1);
                    update(d, 0, big);
                }
                // cerr << "FINI " << hi << endl;
                ll la = n - hi - deadst.query(hi, n);
                // cerr << "FINI " << hi << endl;
                cout << died << " " << la << endl;
            } else {
                ll a, b;
                int c;
                cin >> a >> b >> c;
                --c;
                update(c, a, b);
                if(deads[c]) deadst.upd(i, i+1, -1);
                deads[c] = false;
                // cerr << "UPDATED"  << endl;
            }
        }
        break;
    }
}
