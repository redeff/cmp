#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct Info {
	ll node;
	ll edge;
};

void mer(set<ll> &a, set<ll> &b) {
	if(a.size() < b.size()) swap(a, b);
	for(auto x : b) a.insert(x);
}

struct Node {
	Info info;
	ll alive;
	set<ll> rec;
	vector<Node*> ns;
};

void make_info_cumulative(Node *n, ll i) {
	i += n->info.edge;
	n->info.edge = i;
	for(Node *node : n->ns) make_info_cumulative(node, i);
}

void dead(Node *n) {
	n->rec.insert(n->info.node - n->info.edge);
	n->alive = 1;
	for(Node *node : n->ns) {
		dead(node);
		n->alive += node->alive;
		mer(n->rec, node->rec);
	}

	while(n->rec.begin() != n->rec.end() && *n->rec.begin() + n->info.edge < 0) {
		n->rec.erase(n->rec.begin());
		n->alive--;
	}

	while(n->rec.begin() != n->rec.end() && *n->rec.rbegin() + n->info.edge < n->info.node) {
		n->rec.erase(prev(n->rec.end()));
		n->rec.insert(n->info.node - n->info.edge);
	}
}

ll compute(Node *n) {
	ll res = n->alive;
	for(Node * ch : n->ns) res = max(res, compute(ch));
	return res;
}

Node *build(vector<ll> &nodes, vector<vector<Info>> &tree, ll node, ll dad, ll wei) {
	Node * n = new Node;
	n->info.edge = wei;
	n->info.node = nodes[node];
	for(Info i : tree[node]) {
		if(i.node != dad) {
			n->ns.push_back(build(nodes, tree, i.node, node, i.edge));
		}
	}

	return n;
}

int main() {
	ll n;
	cin >> n;
	vector<ll> nodes(n);
	for(int i = 0; i < n; ++i) cin >> nodes[i];

	vector<vector<Info>> tree(n);
	for(int i = 1; i < n; ++i) {
		ll p, c;
		cin >> p >> c;
		p--;
		tree[i].emplace_back(Info {p, c});
		tree[p].emplace_back(Info {i, c});
	}

	Node* no = build(nodes, tree, 0, -1, 0);
	make_info_cumulative(no, 0);
	dead(no);
	ll k = compute(no);
	cout << n - k << endl;
}
