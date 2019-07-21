#include <bits/stdc++.h>
using namespace std;

typedef vector<string> Quilt;

Quilt A = {"//", "/+"};
Quilt B = {"--", "--"};
Quilt Empty = {""};

Quilt sew(Quilt a, Quilt b) {
	if(a == Empty) return Empty;
	if(b == Empty) return Empty;

	if(a.size() == b.size()) {
		for(int i = 0; i < a.size(); ++i) {
			for(char c : b[i]) a[i].push_back(c);
		}
	} else {
		return Empty;
	}

	return a;
}

char rot_char(char c) {
	if(c == '-') return '|';
	if(c == '|') return '-';
	if(c == '/') return '\\';
	if(c == '\\') return '/';
	return c;
}

Quilt turn(Quilt a) {
	if(a == Empty) return Empty;
	Quilt out(a.back().size());
	for(int i = 0; i < a.size(); ++i) {
		for(int j = 0; j < a[i].size(); ++j) {
			out[j].push_back(rot_char(a[i][j]));
		}
	}

	for(string &s : out) reverse(s.begin(), s.end());

	return out;
}

Quilt parse(string prog) {
	int n = prog.size();

	vector<int> st;
	vector<int> close(n, -1);
	vector<int> comma(n, -1);
	for(int i = 0; i < n; ++i) {
		switch(prog[i]) {
			case '(':
				st.push_back(i);
				break;

			case ')':
				close[st.back()] = i;
				st.pop_back();
				break;

			case ',':
				comma[st.back()] = i;
				break;
		}
	}

	function<Quilt(int, int)> recursive = [&](int l, int r) {
		if(prog[l] == 'A') return A;
		if(prog[l] == 'B') return B;
		if(prog[l] == 's')
			return sew(
				recursive(l+2, comma[l+1]),
				recursive(comma[l+1]+1, close[l+1]));
		if(prog[l] == 't')
			return turn(recursive(l+2, close[l+1]));

		cerr << l << " " << n << endl;
		cerr << "--" << prog[l] << "--" << endl;
		assert(false);
		return Quilt {""};
	};

	return recursive(0, n);
}

int main() {
	vector<string> s = {""};
	{
		ostringstream es;
		es << cin.rdbuf();
		for(char c : es.str()) {
			if(
					c == '(' ||
					c == ')' ||
					c == ',' ||
					c == 'A' ||
					c == 'B' ||
					c == 's' ||
					c == 't') {
				s.back().push_back(c);
			} else if(c == ';') s.emplace_back();
			
		}
	}

	while(s.back() == "") s.pop_back();

	int i = 1;
	for(string p : s) {
		Quilt q = parse(p);
		cout << "Quilt " << i << ":" << endl;
		if(q == Empty) {
			cout << "error" << endl;
		} else {
			for(string r : q) cout << r << endl;
		}
		// cout << endl;
		++i;
	}
}
