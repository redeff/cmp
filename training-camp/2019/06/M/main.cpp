#include <bits/stdc++.h>
#define pb push_back
#define fore(i, b, e) for(int i = b; i < e; ++i)
using namespace std;

const int MAXN = 3e6+100;
// MAXN: max number of nodes or 2 * max number of variables (2SAT)
bool truth[MAXN]; // truth[cmp[i]]=value of variable i (2SAT)
int nvar;int neg(int x){return MAXN-1-x;} // (2SAT)
vector<int> g[MAXN];
int n,lw[MAXN],idx[MAXN],qidx,cmp[MAXN],qcmp;
stack<int> st;
void tjn(int u){
	lw[u]=idx[u]=++qidx;
	st.push(u);cmp[u]=-2;
	for(int v:g[u]){
		if(!idx[v]||cmp[v]==-2){
			if(!idx[v]) tjn(v);
			lw[u]=min(lw[u],lw[v]);
		}
	}
	if(lw[u]==idx[u]){
		int x,l=-1;
		do{x=st.top();st.pop();cmp[x]=qcmp;if(min(x,neg(x))<nvar)l=x;}
		while(x!=u);
		if(l!=-1)truth[qcmp]=(cmp[neg(l)]<0); // (2SAT)
		qcmp++;
	}
}
void scc(){
	memset(idx,0,sizeof(idx));qidx=0;
	memset(cmp,-1,sizeof(cmp));qcmp=0;
	fore(i,0,n)if(!idx[i])tjn(i);
}
// Only for 2SAT:
void addor(int a, int b){g[neg(a)].pb(b);g[neg(b)].pb(a);}
void implies(int a, int b) {
	addor(neg(a), b);
}
bool satisf(int _nvar){
	nvar=_nvar;n=MAXN;scc();
	fore(i,0,nvar)if(cmp[i]==cmp[neg(i)])return false;
	return true;
}

int global_sat;

struct Node {
	vector<int> end;
	int ch[2];
	int satnode;

	Node() {
		ch[0] = -1;
		ch[1] = -1;
		end = {};
		satnode = global_sat++;
	}
};


int main() {
	// cin.tie(0);
	// ios::sync_with_stdio(0);
#define cin fcin
#define cout fcout
	ifstream cin("binary.in");
	ofstream cout("binary.out");
	global_sat = 0;
	// int tr = 0;
	// int fl = neg(tr);
	// addor(tr, tr);
	vector<Node> trie;
	trie.emplace_back();

	int ene;
	cin >> ene;
	vector<string> ns(ene);
	vector<int> sats(ene);
	for(int i = 0; i < ene; ++i) {
		cin >> ns[i];
		sats[i] = global_sat++;
	}

	auto ins = [&](string &s, int decide, int satnode) {
		int curr = 0;
		for(char c : s) {
			implies(satnode, trie[curr].satnode);
			// addor(trie[curr].satnode, neg(satnode));
			int val;
			if(c == '0') val = 0;
			else if(c == '1') val = 1;
			else val = decide;
			if(trie[curr].ch[val] == -1) {
				trie[curr].ch[val] = trie.size();
				trie.emplace_back();
			}
			curr = trie[curr].ch[val];
		}
		trie[curr].end.push_back(satnode);
	};

	for(int i = 0; i < ene; ++i) {
		ins(ns[i], 0, sats[i]);
		ins(ns[i], 1, neg(sats[i]));
	}

	for(Node &p : trie) {
		int k = p.end.size();
		int d = k+1;
		for(int i = 0; i < k; ++i) {
			/*
			implies(p.end[i], global_sat+i);
			// addor(neg(p.end[i]), global_sat+i);
			implies(global_sat+i, neg(p.end[]));
			// addor(neg(global_sat+i), neg(p.end[i+1]));
			if(i!=k-2) addor(neg(global_sat+i), global_sat+i+1);

			addor(neg(p.end[i+1]), global_sat+i+d);
			addor(neg(global_sat+i+d), neg(p.end[i+1]));
			if(i!=k-2) addor(neg(global_sat+i+1+d), global_sat+i+d);
			*/
			implies(p.end[i], global_sat+i+1);
			implies(global_sat+i, neg(p.end[i]));

			implies(global_sat+i, global_sat+i+1);

			implies(global_sat+i+1+d, neg(p.end[i]));
			implies(p.end[i], global_sat+i+d);

			implies(global_sat+i+1+d, global_sat+i+d);
		}

		// implies(p.satnode, global_sat);

		for(int i = 0; i < k; ++i) {
			implies(p.satnode, neg(p.end[i]));
		}
		global_sat += 2*d;
	}

	bool b = satisf(global_sat);
	if(!b) {
		cout << "NO\n";
	} else {
		cout << "YES\n";
		for(int i = 0; i < ene; ++i) {
			for(char c : ns[i]) if(c == '?') cout << !truth[cmp[sats[i]]];
			else cout << c;
			cout << "\n";
			// cout << truth[sats[i]] << " ";
		}
	}
}
