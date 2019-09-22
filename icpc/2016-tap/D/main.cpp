#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
ld EPS = 1e-9;

struct pt {
	ld x, y;
	pt(ld x, ld y): x(x), y(y) {}
	pt(): x(0), y(0) {}
	ld norm2(){return *this**this;}
	ld norm(){return sqrt(norm2());}
	ld operator*(pt p){return x*p.x+y*p.y;}
	pt operator/(ld d){return pt(x/d, y/d);}
	pt operator*(ld d){return pt(x*d, y*d);}
	pt operator+(pt p){return pt(x+p.x, y+p.y);}
	pt operator-(pt p){return pt(x-p.x, y-p.y);}
	ld operator%(pt p){return x*p.y-y*p.x;}
	pt rot(pt r){return pt(*this%r, *this*r);}
	pair<int, int> rnd() {
		int kx = int(round(x));
		int ky = int(round(y));
		if(abs(x - ld(kx)) < EPS && abs(y - ld(ky)) < EPS) return {kx, ky};
		else return {39024821, 2394834};
	}
};

pt ccw90(1, 0);

struct circle {
	pt o; ld r;
	pair<pt, pt> operator^(circle c) {
		ld d = (o-c.o).norm();
		if(d>r+c.r+EPS||d+min(r, c.r)+EPS<max(r, c.r))return {pt(4958,1239481293), pt(4312341, 2112346)};
		ld x=(d*d-c.r*c.r+r*r)/(2*d);
		ld y = sqrt(r*r-x*x);
		pt v=(c.o-o)/d;
		return{o+v*x+v.rot(ccw90)*y, o+v*x-v.rot(ccw90)*y};
	}
};

bool board[201][201];
int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n;
	while(cin >> n) {
		for(int i = 0; i < 201; ++i) for(int j = 0; j < 201; ++j) {
			board[i][j] = false;
		}
		vector<pt> fs(n);
		for(int i = 0; i < n; ++i) {
			int a, b;
			cin >> a >> b;
			a += 100;
			b += 100;
			board[a][b] = true;
			// ns.insert(100000*a + b);
			fs[i] = pt(a, b);
		}

		ld a = (fs[0]-fs[1]).norm();
		ld b = (fs[1]-fs[2]).norm();
		ld c = (fs[0]-fs[2]).norm();

		int tot = 0;
		if(abs(a - b) < EPS) tot++;
		if(abs(b - c) < EPS) tot++;
		if(abs(c - a) < EPS) tot++;
		assert(tot != 2);

		// cerr << a << " " << b << endl;

		int total = 0;
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				ld d = (fs[i] - fs[j]).norm();
				pair<pt, pt> ps = circle {fs[i], a*d/c} ^ circle {fs[j], b*d/c};
				pt p = ps.first;
				pair<int, int> pr = p.rnd();
				if(pr.first >= 0 && pr.first <= 200 && pr.second >= 0 && pr.second <= 200 && board[pr.first][pr.second]) total++;
				else {
					// if(i == 0 && j == 2) cout << p.x << " " << p.y << endl;
				}
				p = ps.second;
				pr = p.rnd();
				if(pr.first >= 0 && pr.first <= 200 && pr.second >= 0 && pr.second <= 200 && board[pr.first][pr.second]) total++;
				else {
					// if(i == 0 && j == 2) cout << p.x << " " << p.y << endl;
				}
			}
		}
		if(tot == 3) total /= 6;
		if(tot == 1) total /= 2;
		cout << total << "\n";
	}
}
