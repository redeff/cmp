#include <bits/stdc++.h>
using namespace std;

vector<string> br(string s) {
	vector<string> out;
	out.push_back("");
	for(char c : s) if(c == ' ') out.push_back("");
	else out.back().push_back(c);
	return out;
}

int main() {
	int w, l, n;
	cin >> w >> l >> n;
	vector<vector<string>> linesi;
	vector<vector<string>> kenni;
	vector<string> words;
	string dummy;
	getline(cin, dummy);
	for(int i = 0; i < n; ++i) {
		string s;
		getline(cin, s);
		kenni.push_back(br(s));
		for(string s : kenni.back()) words.push_back(s);
	}

	string tata;
	while(getline(cin, tata)) {
		linesi.push_back(br(tata));
		for(string s : linesi.back()) words.push_back(s);
	}

	// cerr << linesi.size() << endl;

	sort(words.begin(), words.end());
	vector<vector<int>> lines(linesi.size());
	vector<vector<int>> kenn(words.size());
	for(int i = 0; i < linesi.size(); ++i) {
		for(string s : linesi[i])
			lines[i].push_back(lower_bound(words.begin(), words.end(), s) - words.begin());
	}

	for(int i = 0; i < kenni.size(); ++i) {
		int w = lower_bound(words.begin(), words.end(), kenni[i].front()) - words.begin();
		// cerr << words[w] << " ";
		for(int j = 1; j < kenni[i].size(); ++j) {
			// cerr << kenni[i][j] << " ";
			kenn[w].push_back(
				lower_bound(
					words.begin(),
					words.end(),
					kenni[i][j])
				- words.begin());
		}
		// cerr << endl;
		/*
		for(string s : kenni[i]) {
			for(int i = 0; i < 
			lines[w]
		}
		*/
	}

	for(int i = 0; i < kenn.size(); ++i) if(kenn[i].empty()) kenn[i] = vector<int> {i};
	/*
	for(int i = 0; i < kenn.size(); ++i) {
		cerr << words[i] << " - ";
		for(int j : kenn[i]) {
			 cerr << words[j] << " ";
		}
		cerr << endl;
	}
	*/

	auto step = [&](vector<int> s) {
		vector<int> out;
		for(int i : s) for(int j : kenn[i]) out.push_back(j);
		return out;
	};

	vector<vector<int>> prv = lines;
	while(true) {
		for(auto &v : lines) v = step(v);
		int mx_wid = 0;
		int total = 0;
		for(auto &v : lines) {
			int wi = -1;
			for(int i : v) {
				wi += words[i].size() + 1;
				total += words[i].size();
			}
			mx_wid = max(mx_wid, wi);
		}
		if(mx_wid >= w && total >= l) break;
		else if(prv == lines) {
			cout << "No result" << endl;
			return 0;
		}
		prv = lines;
	}

	string out;
	int linelen = -1;
	for(auto &v : lines) {
		for(int i : v) {
			if(words[i].size() + linelen + 1 >= w) {
				out.push_back('\n');
				linelen = -1;
			} else if(linelen != -1) out.push_back(' '), linelen++;
			for(char c : words[i]) out.push_back(c), linelen++;
			// cout << words[i] << " ";
		}
		out.push_back('\n');
		linelen = -1;
		// cout << endl;
	}
	cout << out;
}
