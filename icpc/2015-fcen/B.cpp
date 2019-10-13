#include <bits/stdc++.h>

using namespace std;
/// Dinitz
typedef long long intl;
#define INF 1000000000
#define MAX_M 12000
#define MAX_N 400
#define forn(i,n) for(int i = 0;i<int(n);i++)
int v[2*MAX_M], l[2*MAX_M];
intl c[2*MAX_M];
int sz[MAX_N], po[MAX_N], r[MAX_N], n ,S, T;
typedef unordered_map<int,intl> Mii;
Mii CAP[MAX_N];
void iniG()
{
	n = 0;
	memset(sz,0,sizeof(sz));
	forn(i,MAX_N)CAP[i].clear();
}
void aEje(int d, int h, intl cap)
{
	if(d == h) return;
	n = max(n,max(d,h));
	pair<Mii::iterator,bool> par = CAP[d].insert(make_pair(h,0));
	if(par.second)
	{
		CAP[h][d] = 0;
		sz[d]++;
		sz[h]++;
	}
	par.first->second+=max(cap,(intl)0);
}

void _aEje(int d, int h, intl capDH, intl capHD)
{
	#define ASIG(d,h,cap) {v[po[d]] = h; c[po[d]] = cap; l[po[d]] = po[h];}
	ASIG(d,h,capDH);
	ASIG(h,d,capHD);
	po[d]++, po[h]++;
}

void _initG(){
	po[0] = 0;
	forn(i,n-1) po[i+1] = po[i] + sz[i];
	forn(u,n) for(auto v : CAP[u])
		if(u < v.first) _aEje(u,v.first,v.second,CAP[v.first][u]);
}
#define forsn(i,s,n) for(int i = s;i<int(n);i++)
intl aumentar()
{
	forn(i,n) r[i] = -1;
	r[S] = 0;
	queue<int> q;
	q.push(S);
	while(!q.empty())
	{
		int x = q.front(); q.pop();
		int d = r[x] + 1, b = po[x];
		if(r[T] >= 0 && d > r[T]) break;
		forsn(j,b,b+sz[x])
		{
			if(c[j]>0 && r[v[j]] < 0)
			{
				r[v[j]] = d;
				q.push(v[j]);
			}
			
		}
	}
	intl res = 0;
	static int path[MAX_N]; path[0] = S;
	static int p[MAX_N], ind[MAX_N];
	memset(p,-1,sizeof(p));
	int pp = 0;
	#define dforn(i,n) for(int i = n-1;i>=0;i--)
	while(pp>=0)
	{
		int x = path[pp];
		if(x == T){
			intl f = INF;
			int pri = 0;
			dforn(i,pp) if(c[ind[i]]<=f) f = c[ind[i]], pri = i;
			forn(i,pp) c[ind[i]] -= f, c[l[ind[i]]] += f;
			res+=f;
			pp = pri;
		}
		else if(++p[x] < sz[x]){
			int j = po[x]+p[x];
			if(p[v[j]] < 0 && c[j] > 0 && r[v[j]] == 1 + r[x])
			{
				ind[pp] = j, path[++pp] = v[j];
			}
		}
		else pp--;
	}
	return res;
}

intl flujo(int ss,int tt)
{
	
	S = ss, T = tt;
	n = max(n,max(S,T)) + 1;
	_initG();
	forn(i,n) po[i] -= sz[i];
	intl res = 0,c;
	do {res += (c = aumentar());}while(c>0);
	return res;
}
bitset<1000> valid;
bool PerfectMatching(vector<int> & obj, vector<bitset<500> > & pad)
{
	valid.reset();
	int N = obj.size()-1;
	iniG();
	/// 0 es el lado A, 2*N+2 es el lado B;
	for(int i = 1;i<=N;i++)
		aEje(0,i,1), aEje(N+i,2*N+2,1);
	for(int i = 1;i<=N;i++)
	{
		for(int j = 1;j<=N;j++)
		{
			if(pad[j][obj[i]] || (valid[j] && obj[i] == 0))
				valid[j] = true, aEje(i,N+j,1);//,aEje(N+j,i,1);
		}
	}
	//cout<<flujo(0,2*N+2)<<" vs "<<N<<endl;
	return (flujo(0,2*N+2) == N);
}
void Caso(int N, int Q)
{
	vector<bitset<500> > pad(N+1);
	for(auto & k : pad) k.reset();
	for(int i = 1;i<=N;i++)
	{
		int b;
		scanf("%d",&b);
		if(b<N) pad[i][0] = true;
		for(int j = 0;j<b;j++)
		{
			int a;
			scanf("%d",&a);
			pad[i][a] = true;
		}
	}
	for(int i = 0;i<Q;i++)
	{
		vector<int> obj(N+1,0);
		int b;
		scanf("%d",&b);
		for(int j = 1;j<=b;j++)
			scanf("%d",&obj[j]);
		if(PerfectMatching(obj,pad))
			printf("Y\n");
		else
			printf("N\n");
	}
	
}
int main()
{
	int N,Q;
	while(cin>>N>>Q)Caso(N,Q);
}
