int tot = 1e6;
struct ShootingGame {
	double findProbability(int a) {
		if(a == tot) return -1;
		if(tot < 2*a) return -1;
		double af = double(a) / double(tot);
		return 1.0 - (1.0 - 2.0 * af) / (1.0 - af);
	}
};
