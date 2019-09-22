/*
 * ProblemaC.cxx
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
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;
void Caso(int N, int M)
{
	vector<vector<int> > h(N+1);
	vector<int> g(N+1,0);
	vector<bool> aprob(N+1,false);
	for(int i = 0;i<M;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		h[a].push_back(b);
		g[b]++;
	}
	queue<int> Q;
	int cantA = 0;
	for(int i = 0;i<N;i++)
	{
		int a;
		scanf("%d",&a);
		aprob[a] = true;
		if(g[a] == 0)
		{
			Q.push(a);
			while(Q.size())
			{
				cantA++;
				int n = Q.front();
				Q.pop();
				for(auto k : h[n])
				{
					g[k]--;
					if(g[k] == 0 && aprob[k] == true)
						Q.push(k);
				}
			}
		}
		printf("%d\n",cantA);
	}
}
int main(int argc, char **argv)
{
	int N,M;
	while(cin>>N>>M)Caso(N,M);
	return 0;
}

