#include <bits/stdc++.h>
using namespace std;

#define fore(i, z, n) for(int i = int(z); i < int(n); ++i)
#define pb push_back

// MOD-1 needs to be a multiple of MAXN !!
// big mod and primitive root for NTT:
#define MOD 2305843009255636993
#define RT 5
#define MAXN (1 << 20)
// typedef long long int CD;
typedef long long int ll;
ll pm(ll a, ll e) {
	ll res = 1;
	while(e) {
		if(e % 2 == 1) {
			res *= a;
			res %= MOD;
		}
		a *= a;
		a %= MOD;
		e /= 2;
	}

	return res;
}
// struct for FFT, for NTT is simple (ll with mod operations)
struct CD {  // or typedef complex<double> CD; (but 4x slower)
	double r,i;
	CD(double r=0, double i=0):r(r),i(i){}
	double real()const{return r;}
	void operator/=(const int c){r/=c, i/=c;}
};
CD operator*(const CD& a, const CD& b){
	return CD(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
CD operator+(const CD& a, const CD& b){return CD(a.r+b.r,a.i+b.i);}
CD operator-(const CD& a, const CD& b){return CD(a.r-b.r,a.i-b.i);}
const double pi=acos(-1.0); // FFT
CD cp1[MAXN+9],cp2[MAXN+9];  // MAXN must be power of 2 !!
int R[MAXN+9];
/*
CD root(int n, bool inv){ // NTT
	ll r=pm(RT,(MOD-1)/n); // pm: modular exponentiation
	return CD(inv?pm(r,MOD-2):r);
}
*/
void dft(CD* a, int n, bool inv){
	fore(i,0,n)if(R[i]<i)swap(a[R[i]],a[i]);
	for(int m=2;m<=n;m*=2){
		double z=2*pi/m*(inv?-1:1); // FFT
		CD wi=CD(cos(z),sin(z)); // FFT
		// CD wi=root(m,inv); // NTT
		for(int j=0;j<n;j+=m){
			CD w(1);
			for(int k=j,k2=j+m/2;k2<j+m;k++,k2++){
				CD u=a[k];CD v=a[k2]*w;a[k]=u+v;a[k2]=u-v;w=w*wi;
			}
		}
	}
	if(inv)fore(i,0,n)a[i]/=n; // FFT
	/*
	if(inv){ // NTT
		CD z(pm(n,MOD-2)); // pm: modular exponentiation
		fore(i,0,n)a[i]=a[i]*z;
	}
	*/
}
vector<ll> multiply(vector<ll>& p1, vector<ll>& p2){
	ll n=p1.size()+p2.size()+1;
	ll m=1,cnt=0;
	while(m<=n)m+=m,cnt++;
	fore(i,0,m){R[i]=0;fore(j,0,cnt)R[i]=(R[i]<<1)|((i>>j)&1);}
	fore(i,0,m)cp1[i]=0,cp2[i]=0;
	fore(i,0,p1.size())cp1[i]=p1[i];
	fore(i,0,p2.size())cp2[i]=p2[i];
	dft(cp1,m,false);dft(cp2,m,false);
	fore(i,0,m)cp1[i]=cp1[i]*cp2[i];
	dft(cp1,m,true);
	vector<ll> res;
	n-=2;
	fore(i,0,n)res.pb((ll)floor(cp1[i].real()+0.5)); // change for NTT
	// fore(i,0,n)res.pb(cp1[i]); // change for NTT
	return res;
}

const int N = 1e5+9;

vector<int> g[N];int n;
bool tk[N];
int fat[N]; // father in centroid decomposition
int szt[N]; // size of subtree
int calcsz(int x, int f){
	szt[x]=1;
	for(auto y:g[x])if(y!=f&&!tk[y])szt[x]+=calcsz(y,x);
	return szt[x];
}
void go(int);
void cdfs(int x=0, int f=-1, int sz=-1){ // O(nlogn)
	if(sz<0)sz=calcsz(x,-1);
	for(auto y:g[x])if(!tk[y]&&szt[y]*2>=sz){
		szt[x]=0;cdfs(y,f,sz);return;
	}
	tk[x]=true;fat[x]=f;
	go(x);
	for(auto y:g[x])if(!tk[y])cdfs(y,x);
}
void centroid(){memset(tk,false,sizeof(tk));cdfs();}

// int depths[MAXN];
ll glob[N];
void go(int root) {
	// vector<int> dist(szt[node], 0);
	vector<vector<ll>> ns;
	int mx = 1;
	function<void(int, int, int)> dfs = [&](int node, int dad, int depth) {
		while(ns.back().size() <= depth) ns.back().push_back(0);
		ns.back()[depth]++;
		mx = max(mx, int(ns.back().size()));
		for(int ch : g[node]) if(ch != dad && !tk[ch]) {
			dfs(ch, node, depth+1);
		}
	};

	for(int ch : g[root]) if(!tk[ch]) {
		ns.emplace_back();
		dfs(ch, root, 1);
	}

	vector<ll> total(mx, 0);
	for(auto &v : ns) for(int i = 0; i < v.size(); ++i) total[i] += v[i];
	assert(total[0] == 0);
	total[0] = 1;
	/*
	cerr << " T ";
	for(int i : total) cerr << i << " ";
	*/
	total = multiply(total, total);
	/*
	cerr << " fft => ";
	for(int i : total) cerr << i << " ";
	cerr << endl;
	*/
	assert(total[0] == 1);
	total[0] = 0;
	// total[0] = 1;
	// assert(total[0] == 1);
	// total[0]--;
	for(int i = 0; i < total.size(); ++i) glob[i] += total[i];
	for(auto &v : ns) {
		/*
		cerr << " V ";
		for(int i : v) cerr << i << " ";
		*/
		v = multiply(v, v);
		/*
		cerr << " fft => ";
		for(int i : v) cerr << i << " ";
		cerr << endl;
		*/
		for(int i = 0; i < v.size(); ++i) glob[i] -= v[i];
	}
}

int main() {
	ll n;
	cin >> n;
	fore(i, 0, n-1) {
		ll a, b;
		cin >> a >> b;
		--a; --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	centroid();
	for(int i = 0; i < n; ++i) glob[i] /= 2;
	vector<bool> sieve(n, true);
	sieve[1] = false;
	ll total = 0;
	ll big = 0;
	for(ll i = 1; i < n; ++i) {
		big += glob[i];
		if(sieve[i]) {
			total += glob[i];
			for(ll k = 2*i; k < n; k += i) {
				sieve[k] = false;
			}
		}
	}
	assert(big == n*(n-1)/2);
	// cerr << big << endl;
	cout << setprecision(10);
	cout << double(total)/double(big) << endl;
}
