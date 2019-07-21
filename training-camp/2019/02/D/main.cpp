#include <bits/stdc++.h>
using namespace std;

#define fore(i, z, n) for(int i = z; i < n; ++i)

long double EPS=1e-8;

vector<int> X,Y;
vector<vector<long double> > A;
vector<long double> b,c;
long double z;
int n,m;
void pivot(int x,int y){
	swap(X[y],Y[x]);
	b[x]/=A[x][y];
	fore(i,0,m)if(i!=y)A[x][i]/=A[x][y];
	A[x][y]=1/A[x][y];
	fore(i,0,n)if(i!=x&&abs(A[i][y])>EPS){
		b[i]-=A[i][y]*b[x];
		fore(j,0,m)if(j!=y)A[i][j]-=A[i][y]*A[x][j];
		A[i][y]=-A[i][y]*A[x][y];
	}
	z+=c[y]*b[x];
	fore(i,0,m)if(i!=y)c[i]-=c[y]*A[x][i];
	c[y]=-c[y]*A[x][y];
}
pair<long double,vector<long double> > simplex( // maximize c^T x s.t. Ax<=b, x>=0
		vector<vector<long double> > _A, vector<long double> _b, vector<long double> _c){
	// returns pair (maximum value, solution vector)
	A=_A;b=_b;c=_c;
	n=b.size();m=c.size();z=0.;
	X=vector<int>(m);Y=vector<int>(n);
	fore(i,0,m)X[i]=i;
	fore(i,0,n)Y[i]=i+m;
	while(1){
		int x=-1,y=-1;
		long double mn=-EPS;
		fore(i,0,n)if(b[i]<mn)mn=b[i],x=i;
		if(x<0)break;
		fore(i,0,m)if(A[x][i]<-EPS){y=i;break;}
		assert(y>=0); // no solution to Ax<=b
		pivot(x,y);
	}
	while(1){
		long double mx=EPS;
		int x=-1,y=-1;
		fore(i,0,m)if(c[i]>mx)mx=c[i],y=i;
		if(y<0)break;
		long double mn=1e200;
		fore(i,0,n)if(A[i][y]>EPS&&b[i]/A[i][y]<mn)mn=b[i]/A[i][y],x=i;
		assert(x>=0); // c^T x is unbounded
		pivot(x,y);
	}
	vector<long double> r(m);
	fore(i,0,n)if(Y[i]<m)r[Y[i]]=b[i];
	return {z,r};
}

long double dist(pair<long double, long double> a, pair<long double, long double> t) {
	long double dx = a.first - t.first;
	long double dy = a.second - t.second;
	return sqrt(dx*dx + dy*dy);
}

int main() {
	int test;
	cin >> test;
	cout << setprecision(20);
	while(test --> 0) {
		int ene;
		cin >> ene;
		vector<pair<long double, long double>> ns(ene);
		for(auto &p : ns) cin >> p.first >> p.second;

		vector<vector<long double>> as;
		vector<long double> bs;
		for(int i = 0; i < ene; ++i) {
			for(int j = i+2; j < ene; ++j) {
				if(j != ene-1 || i != 0) {
					as.emplace_back(ene, 0);
					as.back()[i] = 1;
					as.back()[j] = 1;
					bs.push_back(1e-6 + dist(ns[i], ns[j]));
				}
			}

			// if(i != ene-1) {
				int j = (i+1) % ene;
				as.emplace_back(ene, 0);
				as.back()[i] = -1;
				as.back()[j] = -1;
				bs.push_back(1e-6-dist(ns[i], ns[j]));
			// }
		}
		vector<long double> cs(ene, -1);
		auto p = simplex(as, bs, cs);
		// cerr << " la " << p.second.size() << endl;
		for(long double t : p.second) {
			cout << t << endl;
		}
		cout << endl;
	}
}
