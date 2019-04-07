#include <vector>
#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int test = 0; test < t; ++test) {
        int n, b, f;
        cin >> n >> b >> f;
        vector<vector<bool>> ns(f);
        for(int i = 0; i < f; ++i) {
            ns[i] = vector<bool>(n);
            for(int j = 0; j < n; ++j) {
                ns[i][j] = j / (1 << i) % 2;
            }
            for(bool b : ns[i]) cout << b;
            cout << endl;
            string s;
            cin >> s;
            ns[i].clear();
            for(char c : s) ns[i].push_back(c == '1');
        }
        
        int total = 0;
        vector<int> broken;
        for(int i = 0; i < n; ++i) {
		// for(int b : broken) cerr << b << " ";
		// cerr << endl;
            bool works = true;
            for(int j = 0; j < f; ++j)
                if(ns[total][j] != bool (i & (1 << j)))
                    works = false;
            
            if(works) broken.push_back(i), total++;
        }
        
        for(int b : broken) cout << b << " ";
        cout << endl;
	int s;
	cin >> s;
	if(s == -1) exit(0);
    }
}
