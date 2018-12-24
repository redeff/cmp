#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int ask(ll c, ll d) {
	cout << "? " << c << " " << d << endl;
	int ret;
	cin >> ret;
	return ret;
}

int main() {
	int siz = 30;

	ll eq_mask = 0ll;
	ll known_a = 0ll;
	ll known_b = 0ll;
	int last = ask(0, 0);

	for(int i = siz - 1; i >= 0; --i) {
		int curr = ask(eq_mask ^ (1 << i), 1 << i);		
		int mixed = ask(eq_mask, 1 << i);		
		if(curr != last) { // a[i] != b[i]
			eq_mask ^= 1 << i;
			if(curr == -1) known_a ^= 1 << i;
			else known_b ^= 1 << i;
			last = mixed;
		} else {
			assert(mixed != 0);
			if(mixed == 1) known_a ^= 1 << i, known_b ^= 1 << i;
		}
	}

	cout << "! " << known_a << " " << known_b << endl;
}
