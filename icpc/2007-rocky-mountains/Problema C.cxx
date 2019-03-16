/*
 * Problema C.cxx
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
#include <cstring>
#include <queue> 
using namespace std;
int dist[1001];
pair<int,int> in[1001];

void Caso()
{
	long long N,ini,fin;
	double l1,l2;	
	cin>>N>>ini>>fin>>l1>>l2;
	double L = (l1+l2);
	L *= L;
	long long Li = L;
	ini--,fin--;
	vector<vector<long long> > Ary(N);
	for(int i = 0;i<N;i++)
		dist[i] = 1000000;
	for(int i = 0;i<N;i++)
	{
		cin>>in[i].first>>in[i].second;
		for(int j = 0;j<i;j++)
		{
			long long dx = in[i].first - in[j].first;
			long long dy = in[i].second - in[j].second;
			dx *= dx, dy *= dy;
			long long D = dx + dy;
			if(D <= Li)
				Ary[i].push_back(j), Ary[j].push_back(i);
		}
	}
	queue<int> Q;
	Q.push(ini);
	dist[ini] = 0;
	while(Q.size())
	{
		int node = Q.front();
		Q.pop();
		int c = dist[node] + 1;
		for(auto k : Ary[node])
			if(dist[k] > c)
				dist[k] = c, Q.push(k);
	}
	if(dist[fin] == 1000000)
		cout<<"Impossible"<<endl;
	else
		cout<<dist[fin]<<endl;
}
int main(int argc, char **argv)
{
	int T;
	cin>>T;
	while(T--)
		Caso();
}
/*
1
9 1 4 2.000 3.000
0 7
-6 2 
-3 3
 6 2
 -6 -3
3 -3
6 -3
-3 -7
0 7
*/

