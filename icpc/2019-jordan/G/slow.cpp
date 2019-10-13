#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
using namespace std;

int lp2(int n) {
	int i = 1;
	while(i < n) i *= 2;
	return i;
}

template<class Op, class Val>
struct St {
	vector<Op> lazy;
	vector<Val> data;
	int n;
	St(int _n) {
		n = lp2(_n);
		lazy = vector<Op>(2*n-1, Op::zero());
		data = vector<Val>(2*n-1, Val::init());
	}
	void init(int node, int s, int e, vector<Val> &ini) {
		// cerr << "AAH" << endl;
		if(e == s+1) {
			if(s < ini.size()) data[node] = ini[s];
		} else {
			int m = (s+e)/2;
			init(2*node+1, s, m, ini);
			init(2*node+2, m, e, ini);
			data[node] = data[2*node+1] + data[2*node+2];
		}
	}
	void push(int node, int s, int e) {
		// assert(node < 2*n-1);
		data[node] = data[node].apply(lazy[node], e-s);
		if(e-s > 1) {
			lazy[2*node+1] = lazy[node] * lazy[2*node+1];
			lazy[2*node+2] = lazy[node] * lazy[2*node+2];
		}
		lazy[node] = Op::zero();
	}
	Val query(int node, int s, int e, int a, int b) {
		if(a == b || e <= a || b <= s) return Val::zero();
		push(node, s, e);
		if(a <= s && e <= b) return data[node];
		int m = (s+e)/2;
		return query(2*node+1, s, m, a, b) + query(2*node+2, m, e, a, b);
	}
	void update(int node, int s, int e, int a, int b, Op v) {
		push(node, s, e);
		if(a == b || e <= a || b <= s) return;
		if(a <= s && e <= b) {
			// cerr << "upa " << node << " " << s << " " << v.k << endl;
			lazy[node] = v * lazy[node];
			push(node, s, e);
			// cerr << lazy[node]
			return;
		}
		int m = (s+e)/2;
		update(2*node+1, s, m, a, b, v);
		update(2*node+2, m, e, a, b, v);
		data[node] = data[2*node+1] + data[2*node+2];
	}
	void init(vector<Val> &ini) {init(0, 0, n, ini);}
	Val query(int a, int b) {return query(0, 0, n, a, b);}
	void update(int a, int b, Op v) {return update(0, 0, n, a, b, v);}
};

typedef long long int ll;
struct Sums {
	int n;
	vector<ll> data;
	Sums(int _n, vector<ll> &ini) {
		n = lp2(_n);
		data = vector<ll>(2*n-1);
		init(0, 0, n, ini);
	}

	void init(int node, int s, int e, vector<ll> &ini) {
		if(e-s == 1) {
			if(s < ini.size()) data[node] = ini[s];
			else data[node] = 0;
		} else {
			int m = (s+e)/2;
			init(2*node+1, s, m, ini);
			init(2*node+2, m, e, ini);
			data[node] = data[2*node+1] + data[2*node+2];
		}
	}

	void upd(int node, int s, int e, int index, ll val) {
		if(index < s || e <= index) return;
		if(e-s == 1) {
			data[node] = val;
		} else {
			int m = (s+e)/2;
			upd(2*node+1, s, m, index, val);
			upd(2*node+2, m, e, index, val);
			data[node] = data[2*node+1] + data[2*node+2];
		}
	}

	int ind(int node, int s, int e, ll val) {
		// cerr << node << " " << data[node] << " ACA " << val << endl;
		if(e - s == 1) {
			return data[node] <= val ? e : s;
		} else {
			int m = (s+e)/2;
			if(data[2*node+1] > val) return ind(2*node+1, s, m, val);
			else return ind(2*node+2, m, e, val - data[2*node+1]);
		}
	}

	/*
	ll query(int node, int s, int e, int a, int b) {
		if(s - e )
	}
	*/
};

ll inf = 3000000000000000000;
ll big = 2000000000000000000;
struct MinOp {
	ll k;
	inline static MinOp zero() {
		return MinOp {0};
	}
};

struct MinVal {
	ll k;
	int index;
	inline static MinVal init() {
		return MinVal {inf, 123};
	}
	inline static MinVal zero() {
		return MinVal {inf, 91823};
	}

	inline MinVal apply(MinOp o, int d) {
		return MinVal {k + o.k, index};
	}
};

inline MinOp operator*(MinOp a, MinOp b) {
	return MinOp {a.k + b.k};
}

inline MinVal operator+(MinVal a, MinVal b) {
	if(a.k < b.k) return a;
	else return b;
}

struct SumOp {
	int k;
	inline static SumOp zero() {
		return SumOp {-1};
	}
};

struct SumVal {
	int k;
	inline SumVal apply(SumOp o, int d) {
		if(o.k == -1) return SumVal {k};
		else return SumVal {o.k * d};
	}

	inline static SumVal zero() {
		return SumVal {0};
	}

	inline static SumVal init() {
		return SumVal {0};
	}
};

inline SumOp operator*(SumOp a, SumOp b) {
	if(a.k == -1) return b;
	else return a;
}

inline SumVal operator+(SumVal a, SumVal b) {
	return SumVal {a.k + b.k};
}

int main() {
	// St<MinOp, MinVal> st(100);
	// st.update(0, , MinOp {3});
	// cout << st.query(0, 10).k << endl;
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n;
	cin >> n;

	vector<ll> as(n);
	vector<ll> bs(n);

	forn(i, n) {
		cin >> as[i] >> bs[i];
	}

	St<MinOp, MinVal> st(n);
	{
		vector<MinVal> initial(n);
		forn(i, n) {
			initial[i] = MinVal {as[i], i};
		}

		forn(i, n-1) {
			initial[i+1].k += initial[i].k;
		}

		forn(i, n) initial[i].k += bs[i];
		st.init(initial);
	}

	/*
	auto p = st.query(1, 2);
	cout << p.k << " " << p.index << endl;
	return 0;
	*/

	St<SumOp, SumVal> dead(n);

	Sums partials(n, as);

	auto update = [&](int index, ll a, ll b) {
		st.update(index, n, MinOp {a - as[index]});
		st.update(index, index+1, MinOp {b - bs[index]});

		partials.upd(0, 0, partials.n, index, a);

		as[index] = a;
		bs[index] = b;
	};

	int q;
	cin >> q;
	forn(kjsadfhsdf, q) {
		int t;
		cin >> t;
		if(t == 1) {
			ll x;
			cin >> x;

			/*
			int lo = -1;
			int hi = n;
			while(hi - lo > 1) {
				int mid = (hi+lo)/2;
				ll food = st.query(mid, mid+1).k - bs[mid];
				if(food > x) hi = mid;
				else lo = mid;
			}
			*/
			int hi = min(partials.ind(0, 0, partials.n, x), n);
			// cerr << hi << endl;

			// El primero al que no le alcanza es hi
			vector<int> killed;
			forn(lala, n) {
				auto best = st.query(0, hi);
				// cerr << best.index << " " << best.k << " " << bs[best.index] << endl;
				// assert(best.index < hi);
				if(x > best.k) {
					// assert(dead.query(best.k));
					killed.push_back(best.index);
					update(best.index, as[best.index], big);
					// assert(st.query(best.index, best.index+1).k == big);
				} else break;
			}

			for(int i : killed) {
				// cerr << i << endl;
				update(i, 0, big);
				assert(dead.query(i, i+1).k == 0);
				dead.update(i, i+1, SumOp {1});
			}

			int hungry = n - hi - dead.query(hi, n).k;
			cout << killed.size() << " " << hungry << "\n";
		} else {
			ll a, b;
			int c;
			cin >> a >> b >> c;
			--c;
			update(c, a, b);
			dead.update(c, c+1, SumOp {0});
			// cerr << "UPDATE" << endl;
		}
	}
}
