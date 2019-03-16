#include <bits/stdc++.h>
using namespace std;

#define PI 3.14159265358979

int main() {
	int test;
	cin >> test;
	for(int testcase = 0; testcase < test; ++testcase) {
		if(testcase != 0) cout << endl;
		double m, n, l, r;
		cin >> m >> n >> l >> r;
		r /= 2.0;

		double unit[5];
		unit[4] = PI * r * r;
		unit[3] = (4.0 - PI) * r * r;
		unit[2] = 4 * r * (l - 2 * r);
		unit[1] = (l - 2 * r) * (l - 2 * r);

		double all[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
		for(int i = 1; i < 5; ++i) all[i] += (m * n) * unit[i];

		double edge = 2 * (m + n);

		all[4] -= 0.5 * unit[4] * (edge - 2.0);
		all[3] -= 0.5 * unit[3] * (edge - 2.0);
		all[2] += 0.5 * (unit[4] + unit[3]) * (edge - 4.0);
		all[1] += 0.5 * (unit[4] + unit[3])* 2.0;
		all[2] -= 0.25 * unit[2] * edge;
		all[1] += 0.25 * unit[2] * edge;

		double sum = all[1] + all[2] + all[3] + all[4];
		cout << "Case " << testcase + 1 << ":" << fixed << setprecision(4) << endl;
		for(int i = 1; i < 5; ++i) {
			cout << "Probability of covering " << i;
			cout << " tile" << (i == 1 ? " " : "s") << " = ";
			cout << (100.0 * all[i] / sum) << "%" << endl;
		}
	}
}
