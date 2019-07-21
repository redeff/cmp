/*
 * ProblemaD.cxx
 * 
 * Copyright 2019 Carlos Miguel Soto <reedef@reedef-pc>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#define ll long long 
using namespace std;
ll DistA[2100][2100], DistB[2100][2100], DistC[2200];
vector<vector<pair<ll,ll> > > AryC;
void BFS(int ini, ll Dist[],vector<vector<pair<ll,ll> > > &Ary,ll T, ll C)
{
	for(int i = 0;i<=1200;i++)
		Dist[i] = 1e16;
	Dist[ini] = 0;
	priority_queue<pair<ll,ll> ,vector<pair<ll,ll> >,greater<pair<ll,ll> > > PQ;
	PQ.push({0,ini});
	while(PQ.size())
	{
		auto p = PQ.top();
		PQ.pop();
		int n = p.second;
		ll d = p.first;
		for(auto k : Ary[n])
		{
			ll ld = d + k.second;
			int next = k.first;
			if(Dist[next] > ld)
				Dist[next] = ld, PQ.push({ld,next});
		}
	}
	//cout<<"f1"<<endl;
	for(int i = 0;i<1200;i++)
		if(Dist[i] <= T)
			DistB[ini][i] = C, AryC[ini].push_back({i,C});
} 
int main(int argc, char **argv)
{
	int N,M;
	cin>>N>>M;
	int ini,fin;
	cin>>ini>>fin;
	vector<vector<pair<ll,ll> > > Ary(N+1);
	for(int i = 0;i<M;i++)
	{
		ll a,b,c;
		cin>>a>>b>>c;
		Ary[a].push_back({b,c});
		Ary[b].push_back({a,c});
	}
	AryC.resize(N+1);
	for(int i = 1;i<=N;i++)
	{
		ll T,C;
		cin>>T>>C;
		BFS(i,DistA[i],Ary,T,C);
	}
	BFS(ini,DistC,AryC,0,0);
	if(DistC[fin] == 1e16)
		cout<<-1<<endl;
	else
		cout<<DistC[fin]<<endl;
}
/*
4 4
1 3
1 2 3
1 4 1
2 4 1
2 3 5
2 7
7 2
1 2
7 7
*/
