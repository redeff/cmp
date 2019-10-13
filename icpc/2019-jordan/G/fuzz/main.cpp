#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int n = 100000;
int q = 100000;

ll a = 1000000000ll;
ll b = 1000000000ll;

int main() {
	srand(1190283l);
	cout << n << endl;
	for(int i = 0; i < n; ++i) {
		cout << rand() % a << " " << rand() % b << endl;
	}

	cout << q << endl;
	for(int i = 0; i < q; ++i) {
		int t = rand()%2+1;
		cout << t << " ";
		if(t == 1) {
			cout << rand()%b << endl;
		} else {
			cout << rand()%a << " " << rand()%b << " " << 1+rand()%n << endl;
		}
	}
}
