#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	int testcase = 0;
	while(cin >> s && s != "#") {
		testcase++;
		vector<pair<int, int>> nodes;
		nodes.push_back({0, 0});
		int total = 0;
		int depth = 0;
		int mx_depth = 0;
		for(char c : s) {
			if(c == 'd') {
				nodes.back().second++;
				nodes.push_back({nodes.back().first + nodes.back().second, 0});
				total = max(total, nodes.back().first);
				depth++;
				mx_depth = max(mx_depth, depth);
			} else {
				nodes.pop_back();
				depth--;
			}
		}

		cout << "Tree " << testcase << ": " << mx_depth << " => " << total << endl;
	}
}
