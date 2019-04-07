#include <string>
#include <queue>
#include <iostream>

using namespace std;

int medir(string cad);

string merg(string a, string b) {
	int ap = a.size();
	string s = a;
	for(int bp = b.size() - 1; bp >= 0; --bp) {
		s.insert(s.begin() + ap, b[bp]);
		while(!medir(s)) {
			swap(s[ap], s[ap-1]);
			ap--;
		}
	}
	return s;
}

string secuenciar(int N, string s) {
	priority_queue<pair<int, string>> huffman;
	int total = 0;
	for(char c : s) {
		int lo = 0;
		int hi = N + 1;
		if(c == s.back()) lo = N - total;
		else while(hi - lo > 1) {
			int mid = (hi + lo) / 2;
			string s;
			for(int i = 0; i < mid; ++i) s.push_back(c);
			if(medir(s)) lo = mid;
			else hi = mid;
		}
		total += lo;
		string s;
		for(int i = 0; i < lo; ++i) s.push_back(c);
		huffman.push({-lo, s});
	}

	for(int i = 1; i < s.size(); ++i) {
		auto p1 = huffman.top();
		huffman.pop();
		auto p2 = huffman.top();
		huffman.pop();
		huffman.push({p1.first + p2.first, merg(p1.second, p2.second)});
	}

	return huffman.top().second;
}
