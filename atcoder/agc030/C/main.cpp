#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

int main() {
	int k;
	cin >> k;
	if(k == 1) {
		cout << 1 << endl;
		cout << "1 " << endl;
	} else if(k == 2) {
		cout << 2 << endl;
		cout << "1 2 \n2 1 " << endl;
	} else {
		int n = (k + 3) / 4;
		n *= 2;
		cout << n << endl;

		for(int x = 0; x < n; ++x) {
			for(int y = 0; y < n; ++y) {
				int color = 2 * ((x + y) % n) + x % 2;
				/*
				if(color == k) color--;
				if(n % 4 == 1 && color == k - 2) color--;
				*/
				if(k % 4 == 3) {
					// 0 .. 2n
					if(color == 2 * n - 1) color--;
				} else if (k % 4 == 2) {
					if(color == 2 * n - 1 || color == 2 * n - 2) color = 2 * n - 3;
					else if(color == 2 * n - 3) color--;
				} else if (k % 4 == 1) {
					if(color == 2 * n - 1 || color == 2 * n - 2) color = 2 * n - 4;
					else if(color == 2 * n - 3 || color == 2 * n - 4) color = 2 * n - 5;
					else if(color == 2 * n - 5) color--;
				}
				color++;
				cout << color << " ";
			}
			cout << endl;
		}
	}
}
