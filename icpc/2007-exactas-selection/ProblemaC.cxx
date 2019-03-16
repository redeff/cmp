/*
 * ProblemaC.cxx
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
#include <queue>
#include <vector>
using namespace std;
void Dijstrak(vector<int> & dist, int ori, vector<vector<pair<int,int> > > & Ary)
{
	dist[ori] = 0;
	priority_queue<pair<int,int>,vector<pair<int,int> >, greater<pair<int,int> > > PQ;
	PQ.push({0,ori});
	while(PQ.size())
	{
		pair<int,int> p = PQ.top();
		PQ.pop();
		int n = p.second, c = p.first;
		for(auto k : Ary[n])
		{
			int lc = k.second + c;
			if(lc < dist[k.first])
				dist[k.first] = lc, PQ.push({lc,k.first});
		}
	}	
}
bool Case()
{
	int J,B,N,C,S;
	cin>>J>>B>>N>>C>>S;
	if(J == -1)
		return false;
	vector<vector<pair<int,int> > > Ary(J+1);
	for(int i = 0;i<S;i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		Ary[a].push_back({b,c});
		Ary[b].push_back({a,c});
	}
	vector<int> dB(J+1,2e9),dN(J+1,2e9),dC(J+1,2e9);
	dB[B] = 0, dN[N] = 0, dC[C] = 0;
	Dijstrak(dB,B,Ary);
	Dijstrak(dN,N,Ary);
	Dijstrak(dC,C,Ary);
	int rN = dB[N], rC = dB[C], rT = 0;
	for(int i = 1;i<=J;i++)
	{
		int dn = dB[i] + dN[i];
		int dc = dB[i] + dC[i];
		if(dn == rN && dc == rC)
			rT = max(rT, dB[i]);
	}
	rN -= rT, rC -= rT;
	cout<<rT<<" "<<rN<<" "<<rC<<endl;
	return true;
}
int main(int argc, char **argv)
{
	while(Case());
	return 0;
}

