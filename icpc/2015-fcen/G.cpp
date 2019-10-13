#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <bitset>
#include <bits/stdc++.h>
using namespace std;
typedef long double ldouble;
struct Ary{
	int v, A, B;
	ldouble Evaluar(ldouble t)
	{
		return ldouble(A)*t+ldouble(B);
	}
};
ldouble dis[2000];
int N, M;
bitset<2000> visto;

ldouble Dijstra(ldouble t, vector<vector<Ary> > & Adj)
{
	visto.reset();
	for(int i = 0;i<=N;i++)
		dis[i] = 1e18;
	dis[1] = 0;
	priority_queue<pair<ldouble,int>,vector<pair<ldouble,int> >, greater<pair<ldouble,int> > > PQ;
	PQ.push({0,1});
	while(PQ.size())
	{
		auto p = PQ.top();
		PQ.pop();

		int nod = p.second;
		ldouble d = p.first;
//		cout<<nod<<" = "<<d<<endl;
//		if(d > dis[nod]) continue;
		if(visto[nod]) continue;
		visto[nod] = true;
		for(auto & k : Adj[nod])
		{
			ldouble ld = d + k.Evaluar(t);
			if(ld < dis[k.v])
				dis[k.v] = ld, PQ.push({ld,k.v});
		}
	}
	return dis[N];
}
ldouble EPS = 1e-15;
ldouble Caso()
{
	vector<vector<Ary> > Adj(N+1);
	//int ini,fin;
	//cin>>ini>>fin;
	for(int i = 0;i<M;i++)
	{
		int u,v,A,B;
		scanf("%d %d %d %d",&u,&v,&A,&B);
		Ary ar;
		ar.A = A, ar.B = B;
		ar.v = u;
		Adj[v].push_back(ar);
		ar.v = v;
		Adj[u].push_back(ar);
		
	}
	ldouble t0 = 0, t1 = 24*60;
	while(t1-t0>EPS)
	{
		ldouble dt = (t1-t0)/3.0;
		ldouble t2 = t0+dt;
		ldouble t3 = t0+2*dt;
		ldouble V2 = Dijstra(t2,Adj);
		ldouble V3 = Dijstra(t3,Adj);
		//cout<<t2<<" : "<<V2<<" || "<<t3<<" : "<<V3<<endl;
		if(V2 > V3) t1 = t3;
		else t0 = t2;
	}
	return Dijstra(t0,Adj);
}
int main()
{
	while(cin>>N>>M) cout << fixed << setprecision(5) << Caso() << endl;
}
