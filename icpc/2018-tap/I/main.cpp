#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;

	string s;
	cin >> s;

	int p= 0, m=0;
	for(char c : s) if(c=='P') ++p; else if(c=='N') ++m;

	if(2*p > n) cout << "SI";
	else if(2*m >=n) cout << "NO";
	else cout << "INDECISOS";
	cout << endl;
}
