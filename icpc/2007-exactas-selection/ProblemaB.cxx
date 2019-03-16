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
#include <map>
#include <bitset>
#define ll long long
using namespace std;
pair<ll,ll> ori;
bitset<600> used;
bool Horario(const pair<int,int> & a, const pair<int,int> & b)
{
	ll xa = a.first - ori.first, ya = a.second - ori.second;
	ll xb = b.first - ori.first, yb = b.second - ori.second;
	return xa*yb < xb*ya; 
}
void DFS(pair<int,int> punto, map<pair<int,int>,vector<pair<int,int > > > & mapa, map<pair<int,int>,bool> & used)
{
	if(used[punto])
		return;
	used[punto] = true;
	cout<<punto.first<<" "<<punto.second<<" ";
	for(auto k : mapa[punto])
		DFS(k,mapa,used);
}
bool Case()
{
	map<pair<pair<int,int>,pair<int,int> > , int> edges;
	int N;
	cin>>N;
	if(N==-1)
		return 0;
	for(int i = 0;i<N-2;i++)
	{
		pair<int,int> in[3];
		for(int p = 0;p<3;p++)
			{
				int x,y;
				cin>>x>>y;
				in[p] = {x,y};
				for(int j = 0;j<p;j++)
				{
					pair<pair<int,int>,pair<int,int> > edge;
					edge.first = min(in[j],in[p]);
					edge.second = max(in[j],in[p]);
					edges[edge]++;
				}
				//cout<<x<<" - "<<y<<endl;
			}
	}
	map<pair<int,int>, vector<pair<int,int> > > puntos;
	for(auto k : edges)
	{
		if(k.second == 1)
		{
			puntos[k.first.first].push_back(k.first.second);
			puntos[k.first.second].push_back(k.first.first);
		}
	}
	pair<int,int> k = puntos.begin()->first;
	ori = k;
	if(Horario(puntos[k][1],puntos[k][0]))
		swap(puntos[k][0],puntos[k][1]);
	map<pair<int,int>,bool> used;
	DFS(k,puntos,used);
	cout<<endl;
	return true;
	
}
int main(int argc, char **argv)
{
	while(Case());
	return 0;
/*
 * 
0 0 0 9 5 13 10 9 10 0
0 1 1 1 1 0
-2 3 2 3 2 2 1 2 2 1 2 0 0 -1 2 -1 2 -2 -1 -2
* */
}

