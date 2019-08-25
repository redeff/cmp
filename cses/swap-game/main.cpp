// Swap Game CSES
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1*2*3*4*5*6*7*8*9;

// 0 1 2
// 3 4 5
// 6 7 8
vector<pair<int, int>> swaps = {
	{0, 1}, {1, 2},
	{3, 4}, {4, 5},
	{6, 7}, {7, 8},

	{0, 3}, {3, 6},
	{1, 4}, {4, 7},
	{2, 5}, {5, 8}
};

struct Board {
	int ns[9];
	int encode() {
		int total = 0;
		for(int i = 0; i < 9; ++i) {
			total *= i+1;
			int th = 0;
			for(int j = 0; j < i; ++j) {
				if(ns[i] < ns[j]) th++;
			}
			total += th;
		}
		assert(total < MAXN);
		return total;
	}

	vector<Board> nxt() {
		vector<Board> out;
		for(auto p : swaps) {
			auto b = *this;
			swap(b.ns[p.first], b.ns[p.second]);
			out.push_back(b);
		}
		return out;
	}

	bool operator==(Board b) {
		for(int i = 0; i < 9; ++i) if(ns[i] != b.ns[i]) return false;
		return true;
	}
};

Board target = Board {ns: {1, 2, 3, 4, 5, 6, 7, 8, 9}};

int main() {
	vector<Board> bfs;
	bfs.emplace_back();
	for(int i = 0; i < 9; ++i) cin >> bfs.back().ns[i];
	vector<bool> seen(MAXN, false);
	int dist = 0;
	while(true) {
		vector<Board> nbfs;
		for(Board board : bfs) {
			if(board == target) {
				cout << dist << endl;
				return 0;
			}
			int e = board.encode();
			if(!seen[e]) {
				seen[e] = true;
				for(Board ch : board.nxt()) nbfs.push_back(ch);
			}
		}
		++dist;
		swap(bfs, nbfs);
	}
}
