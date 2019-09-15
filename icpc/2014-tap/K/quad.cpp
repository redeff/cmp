#include <bits/stdc++.h>
using namespace std;

string swp(string st, int a, int b, int c, int d) {
	string p = st.substr(0, a);
	string q = st.substr(a, b-a);
	string r = st.substr(b, c-b);
	string s = st.substr(c, d-c);
	string t = st.substr(d, st.size());
	reverse(q.begin(), q.end());
	for(char &c : q) if(c == 'z') c = 'a'; else c += 1;
	reverse(s.begin(), s.end());
	for(char &c : s) if(c == 'z') c = 'a'; else c += 1;

	return p + s + r + q + t;
}

int main() {
	srand(120374231);
	cin.tie(0);
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t --> 0) {
		string s;
		int n;
		cin >> s >> n;
		for(int i = 0; i < n; ++i) {
			/*
			string out;
			collect(treap, out);
			cout << out << endl;
			*/
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			--a; --c;
			s = swp(s, a, b, c, d);
		}

		cout << s << endl;
	}
}
