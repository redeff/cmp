#include <bits/stdc++.h>
#define forn(i, n) for(int i = 0; i < n; ++i)
using namespace std;

typedef long double ld;

struct Conn {
	int to;
	ld wei;
};

struct Quad {
	ld a, b, c;

	// Quad(): a(0), b(0), c(0) {}

	Quad operator+(Quad q) {
		return Quad {a+q.a, b+q.b, c+q.c};
	}

	Quad operator-(Quad q) {
		return Quad {a-q.a, b-q.b, c-q.c};
	}

	// P(x+t)
	Quad at(ld t) {
		// a(x+t)² + b(x+t) + c =
		// ax² + 2axt + at² + bx + bt + c =
		// ax² +(2at + b)x + at² + bt + c
		return Quad {a, 2*a*t + b, a*t*t + b*t + c};
	}

	// P(-x)
	Quad neg() {
		return Quad {a, -b, c};
	}

	ld eval(ld x) {
		return a*x*x + b*x + c;
	}

	ld lowest() {
		return -b/(2*a);
	}

	ld minin(ld a, ld b) {
		if(a > b) swap(a, b);
		ld mn = lowest();
		mn = max(mn, a);
		mn = min(mn, b);

		return eval(mn);
	}

	void print() {
		cout << a << "x² + " << b << "x + " << c << " ";
	}
};

int main() {
	int n;
	cin >> n;

	vector<vector<Conn>> graph(n);
	forn(i, n-1) {
		int a, b;
		ld wei;
		cin >> a >> b >> wei;
		--a; --b;
		graph[a].push_back(Conn {b, wei});
		graph[b].push_back(Conn {a, wei});
	};

	vector<ld> len(n, 0);
	vector<Quad> down(n, Quad {1, 0, 0});
	function<void(int, int)> dfs_down = [&](int node, int dad) {
		for(Conn conn : graph[node]) if(conn.to != dad) {
			len[conn.to] = conn.wei;
			dfs_down(conn.to, node);
			down[node] = down[node] + down[conn.to].at(conn.wei);
		}
	};
	dfs_down(0, 0);
	/*
	for(Quad q : down) q.print(), cout << endl;
	cout << endl;
	*/

	vector<Quad> up(n, Quad {0, 0, 0});
	function<void(int, int)> dfs_up = [&](int node, int dad) {
		for(Conn conn : graph[node]) if(conn.to != dad) {
			up[conn.to] =
				up[node]
				+ (down[node] - down[conn.to].at(conn.wei)).neg();
			up[conn.to] = up[conn.to].at(-conn.wei);

			dfs_up(conn.to, node);
		}
	};
	dfs_up(0, 0);
	/*
	for(Quad q : up) q.print(), cout << endl;
	cout << endl;
	*/

	ld best = numeric_limits<ld>::infinity();
	forn(i, n) {
		best = min(best, (up[i] + down[i]).minin(0, len[i]));
	}

	ld lg = log10(best);
	ld p = pow(10, floor(lg));
	cout << setprecision(5) << fixed;
	best /= p;
	assert(best < 10.0);
	assert(1.0 <= best);
	cout << best << " " << int(floor(lg)+0.5) << endl;
}
