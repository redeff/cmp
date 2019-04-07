#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

template<class T>
void mer(multiset<T> &a, multiset<T> &b) {
	if(a.size() < b.size()) swap(a, b);
	for(auto x : b) a.insert(x);
}

struct Node {
	ll wei;
	ll edge;
	ll alive;
	multiset<pair<ll, ll>> sub;
	vector<Node*> children;
	ll val() {
		return edge - wei;
	}
};

void make_info_cumulative(Node *node, ll acc) {
	node->edge += acc;
	for(Node *child : node->children) make_info_cumulative(child, node->edge);
}

void alive(Node *node) {
	// a child dies if dist(node, child) > child->wei <=>
	// child->edge - node->edge > child->wei
	// child->edge - child->wei > node->edge
	// child->val() > node->edge
	//
	// a child is replaced if child->val() <= node->val()
	// 
	// so a child survives iff 
	// node->val() < child->val() <= node->edge
	
	node->alive = 1;
	for(Node *child : node->children) {
		alive(child);
		node->alive += child->alive;
		mer(node->sub, child->sub);
	}

	ll total = 1;

	while(!node->sub.empty() && (*node->sub.rbegin()).first > node->edge) {
		node->alive -= (*node->sub.rbegin()).second;
		node->sub.erase(prev(node->sub.end()));
	}

	while(!node->sub.empty() && (*node->sub.begin()).first <= node->val()) {
		total += (*node->sub.begin()).second;
		node->sub.erase(node->sub.begin());
	}

	node->sub.insert({node->val(), total});
}

ll total(Node* node) {
	cerr << node->wei << " " << node->alive << endl;
	ll res = node->alive;
	for(Node *child : node->children) res = max(res, total(child));
	cerr << "end" << endl;
	return res;
}


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

Node *build(vector<ll> &nodes, vector<vector<Info>> &tree, ll node, ll dad, ll wei) {
	Node * n = new Node;
	n->edge = wei;
	n->wei = nodes[node];
	for(Info i : tree[node]) {
		if(i.node != dad) {
			n->children.push_back(build(nodes, tree, i.node, node, i.edge));
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
	alive(no);
	ll k = no->alive;
	cout << n - k << endl;
}
