#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n;
	cin >> n;

	vector<int> pruefer(n-2);
	vector<int> deg(n, 1);
	for(int &i : pruefer) {
		cin >> i;
		--i;
		deg[i]++;
	}

	priority_queue<int> pq;
	for(int i = 0; i < n; ++i) if(deg[i] == 1) pq.push(-i);
	for(int i : pruefer) {
		int t = -pq.top();
		pq.pop();

		cout << (t+1) << " " << (i+1) << "\n";
		deg[i]--;
		if(deg[i] == 1) pq.push(-i);
	}

	int a, b;
	a = pq.top(); pq.pop();
	b = pq.top(); pq.pop();
	cout << (1-a) << " " << (1-b) << "\n";
}
