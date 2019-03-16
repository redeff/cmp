#include <bits/stdc++.h>
using namespace std;

vector<string> note_g = {
	"  |\\",
	"  | ",
	" x| "
};

vector<string> sharp_g = {
	"  |\\",
	"  | ",
	"#x| "
};

vector<string> score_g = {
	"                        |",
	"------------------------|",
	"                        |",
	"------------------------|",
	"                        |",
	"------------------------|",
	"                        |",
	"------------------------|",
	"                        |",
	"------------------------|",
	"                        |"
};

void repl(vector<string> &a, vector<string> &b, int vert, int hor) {
	for(int i = 0; i < b.size(); ++i) for(int j = 0; j < b[i].size(); ++j) {
		if(b[i][j] != ' ') a[i+vert][j+hor] = b[i][j];
	}
}

void add(vector<string> &score, int vert, int hor, bool is_sharp) {
	repl(score, is_sharp ? sharp_g : note_g, score.size()-4 - vert, 1 + 6 * hor + hor / 4);
}

int main() {
	int n;
	while(cin >> n && n != -1) {
		int num_lines = (n + 15) / 16;
		vector<pair<bool, int>> notes(n);
		for(int i = 0; i < n; ++i) {
			string note;
			cin >> note;
			notes[i].first = note.back() == '#';
			notes[i].second = (note.front() - 'A' + 3) % 7;
		}

		vector<vector<string>> score(num_lines, vector<string>(score_g.size()));
		for(int x = 0; x < num_lines; ++x) {
			for(int i = 0; i < score_g.size(); ++i) {
				score[x][i].push_back('|');
				for(int j = 0; j < 4; ++j) {
					for(char c : score_g[i]) score[x][i].push_back(c);
				}
			}
		}
		for(int i = 0; i < n; ++i) add(score[i / 16], notes[i].second, i % 16, notes[i].first);

		for(int i = 0; i < num_lines; ++i) {
			for(auto & s : score[i]) {
				cout << (i == 0 ? '|' : ' ');
				cout << s;
				if(i == num_lines - 1) cout << '|';
				cout << endl;
			}
		}

		cout << endl;
	}
}
