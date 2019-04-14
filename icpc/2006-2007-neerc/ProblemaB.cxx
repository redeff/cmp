/*
 * ProblemaB.cxx
 * 
 * Copyright 2019 Unknown <reedef@reedef-pc>
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
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
ll cantUsos[20000], largo[20000], N,K;
vector<vector<pair<int,int> > > Ary;
ll DFS(int n, int p)
{
	ll totH = 1;
	for(auto k : Ary[n])
	{
		if(k.first!=p)
		{
			ll lt = DFS(k.first,n);
			ll res = N-lt;
			cantUsos[k.second] = (lt*res);
			totH += lt;
		}
	}
	return totH;
	
}
ll Sh,Sc;
vector<pair<ll,int> > Res;
int main(int argc, char **argv)
{
	cin>>N>>K>>Sh>>Sc;
	Ary.resize(N+1);
	for(int i = 1;i<N;i++)
	{
		ll a,b;
		cin>>a>>b>>largo[i];
		Ary[a].push_back({b,i});
		Ary[b].push_back({a,i});
	}
	DFS(1,-1);
	for(int i = 1;i<N;i++)
	{
		ll TotM = cantUsos[i] * largo[i];
		Res.push_back({TotM,i});
	}
	if(Sc > Sh)
		sort(Res.rbegin(),Res.rend());
	else
		sort(Res.begin(),Res.end());
	for(int i = 0;i<K;i++)
		cout<<(Res[i].second)<<" ";
	return 0;
}

