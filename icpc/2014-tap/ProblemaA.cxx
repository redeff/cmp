/*
 * ProblemaA.cxx
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
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
vector<vector<int> > Papers, Autors;
int N,A, num[200000];
bool visto[200000];
int D = 0, S = 0, M = -1;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > PQ;
void ProcesarPaper(int p)
{
	if(visto[p]) return;
	visto[p] = true;
	int dis = 1e9;
	for(auto k : Papers[p])
		if(num[k] > -1)
			dis = min(dis,num[k]);
	dis++;
	for(auto k : Papers[p])
	{
		if(num[k] == -1 || num[k] > dis)
		{
			num[k] = dis;
			PQ.push({dis,k});
		}
	}
}
void ProcesarAutor(int autor)
{
	for(auto k : Autors[autor])
		if(visto[k] == false)
			ProcesarPaper(k);
		
}
int main(int argc, char **argv)
{
	memset(num,-1,sizeof(num));
	memset(visto,0,sizeof(visto));
	cin>>A>>N;
	Papers.resize(A+1),Autors.resize(N+1);
	for(int i = 0;i<A;i++)
	{
		int C;
		scanf("%d",&C);
		for(int j = 0;j<C;j++)
		{
			int a;
			scanf("%d",&a);
			Autors[a].push_back(i);
			Papers[i].push_back(a);
		}
	}
	PQ.push({0,1});
	while(PQ.size())
	{
		auto k = PQ.top();
		PQ.pop();
		if(k.first == num[k.second])
			ProcesarAutor(k.second);
	} 
	num[1] = 0;
	ProcesarAutor(1);
	for(int i = 1;i<=N;i++)
		if(num[i]!=-1)
		{	
			S+=num[i];
			M = max(M,num[i]);
			D++;
		}
	cout<<D<<" "<<M<<" "<<S<<endl;
	return 0;
}

