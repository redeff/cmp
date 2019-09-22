#include <bits/stdc++.h>
using namespace std;

struct Game {
	// int best_side[2];
	int best_todo[2];
	int sum;
	int best[2];

	Game() {
		best_todo[0] = 0;
		best_todo[1] = 0;
		// sum={0,0};
		sum = 0;
		best[0] = 0;
		best[1] = 0;
	}
	int add(int val, int size, bool side) {
		// cerr << val << " " << size << " " << side << endl;
		assert(size >= 0);
		assert(val >= 0);
		int a = best[side] - best[1-side] + val;
		int b = val + size - best_todo[1-side];
		if(a > b) {
			best[side] += val;
		} else {
			best[side] = val + size;
			assert(best_todo[1-side] >= best[1-side]);
			best[1-side] = best_todo[1-side];
		}

		sum += val;
		best_todo[1-side] = max(best_todo[1-side], sum + size);
		// best_side[side] = max(best_side[side], size);
		best_todo[side] = max(best_todo[side], size);
		best_todo[side] += val;
		// best_side[side] += val;
		assert(best_todo[1-side] >= best[1-side]);
		assert(best_todo[side] >= best[side]);
		return max(a, b);
	}
};

int main() {
	int n;
	while(cin >> n) {
		int s, e;
		cin >> s >> e;
		--s; --e;

		vector<int> ns(n);
		for(int &i : ns) cin >> i;

		vector<vector<int>> graph(n);
		for(int i = 0; i < n-1; ++i) {
			int a, b;
			cin >> a >> b;
			--a; --b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		auto dist = [&](int root) -> vector<int> {
			vector<int> out(n, -1);
			function<void(int, int, int)> dfs = [&](int node, int dad, int depth) {
				out[node] = depth;
				for(int ch : graph[node]) if(ch != dad) {
					dfs(ch, node, depth+1);
				}
			};
			dfs(root, root, 0);
			return out;
		};

		// auto dist_s = dist(s);
		auto dist_e = dist(e);

		vector<int> mn;
		vector<bool> no(n, false);
		function<void(int)> dfs = [&](int node) {
			mn.push_back(node);
			no[node] = true;
			if(node == e) return;
			for(int ch : graph[node]) if(dist_e[ch] < dist_e[node]) dfs(ch);
		};

		dfs(s);

		vector<int> sizes(n, 0);
		function<void(int, int)> si_dp = [&](int node, int dad) {
			if(no[node]) return;
			// sizes[node] = ns[node];
			for(int ch : graph[node]) if(ch != dad) {
				si_dp(ch, node);
				sizes[node] = max(sizes[node], sizes[ch]);
			}
			sizes[node] += ns[node];
		};

		int k = int(mn.size());
		vector<int> sub(k, 0);
		vector<int> val(k, 0);
		for(int i = 0; i < k; ++i) {
			val[i] = ns[mn[i]];
			for(int ch : graph[mn[i]]) if(!no[ch]) {
				si_dp(ch, ch);
				sub[i] = max(sub[i], sizes[ch]);
			}
		}

		int mid = (k-1)/2;
		Game game = Game();
		int res;
		for(int i = 0; i < k; ++i) {
			int side = (i+k+1) % 2;

			int index = mid;
			if(side == 0) index -= i/2;
			else index += 1+i/2;
			if(i == k-1) assert(index == 0);
			if(0 <= index && index < k) {
				res = game.add(val[index], sub[index], 1-side);
			} else {
				// cout << k << " " << index << endl;
				assert(false);
			}
		}
		cout << res << endl;
	}
}
