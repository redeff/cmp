/*
 * ProblemaI.cxx
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
#include <queue>
#include <cstring>
using namespace std;
int mx[] = {1,0,-1,0}, my[] = {0,1,0,-1}, N,M;
int in[600][600];
int dist[600][600];
bool Legal(int y, int x, int t)
{
	if(y <= 0 || y > N) return false;
	if(x <= 0 || x > M) return false;
	if(t >= in[y][x]) return false;
	if(dist[y][x] != -1) return false;
	return true;
}
bool Intentar(int t)
{
	memset(dist,-1,sizeof(dist));
	dist[1][1] = t;
	queue<pair<int,int> > Q;
	Q.push({1,1});
	while(Q.size())
	{
		auto n = Q.front();
		int i = n.first, j = n.second, d = dist[i][j];
		Q.pop();
		for(int k = 0;k<4;k++)
		{
			int x = j + mx[k], y = i + my[k];
			if(Legal(y,x,d+1))
				dist[y][x] = d+1, Q.push({y,x});
		}
	}
	//cout<<t<<" = "<<endl;
	//for(int i = 0;i<N;i++)
	//{
	//	for(int j = 0;j<M;j++)
	//}
	return (dist[N][M]!=-1);
}
int main(int argc, char **argv)
{
	cin>>N>>M;
	for(int i = 1;i<=N;i++)
		for(int j = 1;j<=M;j++)
			cin>>in[i][j];
	if(Intentar(0) == false)
	{
		cout<<-1<<endl;
		return 0;
	}
	int ini = 0, fin = in[1][1];
	while(fin-ini>1)
	{
		int m = (ini+fin)/2;
		if(Intentar(m))
			ini = m;
		else
			fin = m;
	}
	cout<<ini<<endl;
	return 0;
}

