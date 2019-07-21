#include <bits/stdc++.h>
#define mp make_pair
using namespace std;

pair<int, int> operator+(pair<int, int> a, pair<int, int> b) {
	return {a.first + b.first, a.second + b.second};
}

vector<pair<int, int>> knight = {
	{1, 2},
	{1, -2},
	{-1, 2},
	{-1, -2},
	{2, 1},
	{2, -1},
	{-2, 1},
	{-2, -1}
};

vector<pair<int, int>> rook = {
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0}
};

vector<pair<int, int>> bishop = {
	{1, 1},
	{-1, 1},
	{1, -1},
	{-1, -1}
};

struct State {
	pair<int, int> kni;
	pair<int, int> roo;
	pair<int, int> bis;
	int turn;
	int mn;
	int encode() {
		int total = turn;
		total *= 8;
		total += kni.first;
		total *= 8;
		total += kni.second;
		total *= 8;
		total += roo.first;
		total *= 8;
		total += roo.second;
		total *= 8;
		total += bis.first;
		total *= 8;
		total += bis.second;
		// assert(total < 8*8*8*8*8*8*8);
		return total;
	}

	bool valid(pair<int, int> ab) {
		int a = ab.first;
		int b = ab.second;
		bool res = (0 <= a) && (a < 8) && (0 <= b) && (b < 8)
			&& ab != roo
			&& ab != kni
			&& ab != bis;
		/*
		if(!res) {
			cout << a << " " << b << endl;
		}
		*/
		return res;
	}

	bool operator==(State s) {
		return true
			&& kni == s.kni
			&& roo == s.roo
			&& bis == s.bis
			;
	}

	// Knight, Rook & Bishop
	vector<State> nxt() {
		vector<State> total;
		switch(turn){
			case 0:
				for(auto d : knight) {
					if(valid(d + kni)) {
						State s = *this;
						s.turn += 1;
						s.turn %= 3;
						s.kni = d + kni;
						total.push_back(s);
					}
				}
				break;
			case 1:
				for(auto d : rook) {
					pair<int, int> curr = roo + d;
					while(valid(curr)) {
						State s = *this;
						s.roo = curr;
						s.turn += 1;
						s.turn %= 3;
						total.push_back(s);
						curr = curr + d;
					}
				}
				break;
			case 2:
				for(auto d : bishop) {
					pair<int, int> curr = bis + d;
					while(valid(curr)) {
						State s = *this;
						s.turn += 1;
						s.turn %= 3;
						s.bis = curr;
						total.push_back(s);
						curr = curr + d;
					}
				}
				break;
		}
		// cerr << total.size() << endl;
		return total;
	}
};

const int MAXN = 8*8*8*8*8*8*3*10;

int main() {
	int test;
	cin >> test;
	while(test --> 0) {
		vector<bool> dp(MAXN, false);
		State s;
		cin
			>> s.kni.first
			>> s.kni.second
			>> s.roo.first
			>> s.roo.second
			>> s.bis.first
			>> s.bis.second;
		s.turn = 0;
		State e;
		e.kni = s.bis;
		e.roo = s.kni;
		e.bis = s.roo;
		State e1 = e;
		e1.turn = 0;
		State e2 = e;
		e2.turn = 1;
		State e3 = e;
		e3.turn = 2;
		vector<State> bfs = {s};
		int dist = 0;
		while(!bfs.empty()) {
			vector<State> nbfs;
			for(State a : bfs) {
				if(e1 == a || e2 == a || e3 == a) {
					cout << dist << endl;
					goto next_case;
				}
				// cerr << a.encode() << endl;
				if(dp[a.encode()]) continue;
				dp[a.encode()] = true;
				for(State t : a.nxt()) {
					nbfs.push_back(t);
				}
			}
			swap(bfs, nbfs);
			dist++;
		}
		cout << -1 << endl;
next_case:;
	}
}
