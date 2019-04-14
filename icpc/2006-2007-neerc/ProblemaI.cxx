/*
 * ProblemaI.cxx
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
#include <cstdio>
#include <vector>
using namespace std;
int grado[1001], Cused = 0;
bool used[1001];
vector<vector<int> > Ary;
void DFS(int n, int & E, int & R, int & Cnod)
{
	if(used[n])
		return;
	Cused++;
	Cnod++;
	used[n] = 1;
	if(grado[n] > 2)
	{
		R += 1;
		E+=grado[n]%2 ;
	}
	for(auto k : Ary[n])
		DFS(k,E,R,Cnod);
}
int main(int argc, char **argv)
{
	int N,M, R = 0, E = 0;
	cin>>N>>M;
	Ary.resize(N+1);
	for(int i = 0;i<M;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		grado[a]++,grado[b]++;
		E += (a==0) + (b==0);
		if(a > 0 && b > 0)
			Ary[a].push_back(b), Ary[b].push_back(a);
	}
	R += (E+1)/2;
	int Rn = 0;
	for(int i = 1;i<=N;i++)
		if(grado[i])
			Rn++;
	for(int i = 1;i<=N;i++)
	{
		int Rl = 0, El = 0, Cl = 0;
		DFS(i,El,Rl,Cl);
		if(Cl > 0)
		{
	//		cout<<i<<" = "<<Rl<<" . "<<El<<" . "<<Cl<<endl;
			if(El == 0 && Cl < Rn)
			{
				El += 2;
				Rl = max(1,Rl);
			} 
			R += Rl;
			E += El;
		}
	}
	R += (E+1)/2;
	cout<<R<<endl;
}

