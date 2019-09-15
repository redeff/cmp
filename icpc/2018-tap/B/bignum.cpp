#include <iostream>
#include <assert.h>
using namespace std;

// typedef long long int ll;

const int N = 100;
const int mod = (1<<12);

struct ll {
	int part[N];
	ll() {
		for(int i = 0; i < N; ++i) part[i] = 0;
	}
	ll(unsigned long long l) {
		for(int i = 0; i < N; ++i) part[i] = 0;
		int i = 0;
		while(l != 0) {
			assert(i < N);
			part[i] = l % mod;
			l /= mod;
			++i;
		}
	}

	ll half() {
		ll out = ll();
		for(int i = N-1; i>= 0; --i) {
			if(part[i] % 2 != 0) out.part[i-1] += mod/2;
			out.part[i] += part[i] / 2;
		}

		return out;
	}

	unsigned long long to_ll() {
		unsigned long long out = 0;
		for(int i = N-1; i >= 0; --i) {
			out *= mod;
			out += part[i];
		}

		return out;
	}
};

ll operator*(ll a, ll b) {
	ll out = ll();
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j <= i; ++j) {
			out.part[i] += a.part[j] * b.part[i-j];
		}

		if(i != N-1) out.part[i+1] += out.part[i]/mod;
		out.part[i] %= mod;

		if(i != N-1 && out.part[i] < 0) {
			out.part[i+1]--;
			out.part[i] += mod;
		}
	}

	return out;
}

ll operator+(ll a, ll b) {
	ll out = ll();
	for(int i = 0; i < N; ++i) {
		out.part[i] += a.part[i] + b.part[i];

		if(i != N-1) out.part[i+1] += out.part[i]/mod;
		out.part[i] %= mod;

		if(i != N-1 && out.part[i] < 0) {
			out.part[i+1]--;
			out.part[i] += mod;
		}
	}

	return out;
}

ll red() {
	unsigned long long lg;
	cin >> lg;
	return ll(lg);
}

bool operator<(ll a, ll b) {
	for(int i = N-1; i >= 0; --i) {
		if(a.part[i] < b.part[i]) return true;
		if(a.part[i] > b.part[i]) return false;
	}
	return false;
}

ll operator-(ll a, ll b) {
	ll out = ll();
	for(int i = 0; i < N; ++i) {
		out.part[i] += a.part[i] - b.part[i];

		if(i != N-1) out.part[i+1] += out.part[i]/mod;
		out.part[i] %= mod;

		if(i != N-1 && out.part[i] < 0) {
			out.part[i+1]--;
			out.part[i] += mod;
		}
	}

	return out;
}

// 1 + 2 + .. + k
ll ari(ll k) {
	return (k * (k+ll(1))).half();
}

int main() {
	ll d = red();
	ll m = red();
	ll a = red();
	ll n = red();
	ll b = red();

	a = a-d;
	b = b - d;

	auto con_tantos = [&](ll k) {
		if(!(m < k)) {
			// a + 2a + 3a + .. + ka;
			return ari(k) * a;
		} else {
			// a + 2a + 3a + .. + ma + (ma + b) + (ma + 2b) + ..
			return ari(m) * a + m*a*(k-m) + ari(k-m) * b; 
		}
	};

	ll lo = 0;
	ll hi = n+m;

	while(ll(1) < hi - lo) {
		ll mid = (hi + lo).half();
		// cerr << mid.to_ll() << endl;
		if(con_tantos(mid) < d) {
			lo = mid;
		} else hi = mid;
	}

	if(con_tantos(hi) < d) {
		cout << "-1" << endl;
	} else {
		cout << hi.to_ll() << endl;
	}
}
