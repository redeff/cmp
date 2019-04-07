#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

struct Line {
	int a;
	int from;
	int to;
};

// A[index] += delta;
void set_ft(int index, int delta, vector<int> &ft) {
	assert(index > 2);
	for(int x = index; x < int(ft.size()); x += x & -x) {
		ft[x] += delta;
	}
}

// sum A[1..index]
int get_ft(int index, vector<int> &ft) {
	assert(index > 2);
	int total = 0;
	for(int x = index; x; x -= x & -x) {
		total += ft[x];
	}
	return total;
}

int main() {
#ifndef LOLOLOL
	ifstream cin("autodromo.in");
	ofstream cout("autodromo.out");
#endif
	vector<Line> ls[2];
	for(int g = 0; g < 2; ++g) {
		int n;
		cin >> n;
		vector<array<int, 2>> ps(n, {0, 0});
		for(int i = 0; i < n; ++i) {
			cin >> ps[i][0] >> ps[i][1];
			ps[i][0] += 10;
			ps[i][1] += 10;
		}

		for(int i = 0; i < n; ++i) {
			int pr = (i == 0) ? (n-1) : (i-1);
			int d = (ps[pr][0] == ps[i][0]) ? 1 : 0;
			// ls[1] = ver
			// ls[0] = hor
			// assert(ps[pr][0] == ps[i][0] || ps[pr][1] == ps[i][1]);
			ls[d].push_back(Line {ps[i][1-d], ps[i][d], ps[pr][d]});
			if(ls[d].back().from > ls[d].back().to)
				swap(ls[d].back().from, ls[d].back().to);
		}
	}

	struct Event {
		int point;
		int a;
		int b;
		int type;
		bool operator<(const Event o) const {
			if(point == o.point) return type < o.type;
			else return point < o.point;
		}
	};

	vector<Event> events;
	for(Line l : ls[0]) {
		events.push_back(Event {l.from, l.a, -1, 1});
		events.push_back(Event {l.to, l.a, -1, 0});
	}

	for(Line l : ls[1]) {
		events.push_back(Event {l.a, l.from, l.to, 2});
	}

	sort(events.begin(), events.end());

	vector<int> ft(70000, 0);
	
	int total = 0;
	for(Event e : events) {
		if(e.type == 1) set_ft(e.a, 1, ft);
		else if(e.type == 0) set_ft(e.a, -1, ft);
		else if(e.type == 2 && e.a + 2 <= e.b)
			total += get_ft(e.b-1, ft) - get_ft(e.a, ft);

		/*
		for(int i = 0; i < 20; ++i) {
			cerr << get_ft(i+1, ft) - get_ft(i, ft) << " ";
		}
		cerr << endl;
		*/
	}
	cout << total << endl;
}
