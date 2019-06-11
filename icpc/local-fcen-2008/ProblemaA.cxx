/*
 * ProblemaA.cxx
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
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <iostream>
#include <cstdio>
#include <map>
#include <unordered_map>
#define double float
#include <bitset>
using namespace std;
int Euclides(int a, int b)
{
	if(b == 0)
		return a;
	return Euclides(b,a%b);
}
double Pendiente(pair<double,double> A, pair<double,double> B)
{
	if(A.first == B.first)
		return 1000000;
	double dx = A.first - B.first, dy = A.second - B.second;
	return dy/dx;
	
}
bitset<3000> used;
pair<double,double> P[2000];
bool Caso()
{
	int N;
	used.reset();
	scanf("%d",&N);
	//cin>>N;
	if(N == -1)
		return false;
	pair<double,double> VC;
	map<pair<double,double>,int> Cont;
	for(int i = 0;i<N;i++)
	{
		if(used[i])
			continue;
		//cin>>P[i].first>>P[i].second;
		scanf("%f %f",&P[i].first,&P[i].second);
		VC.first += P[i].first, VC.second += P[i].second;
	}
	VC.first /= double(N);
	VC.second /= double(N);
	//cout<<" ---- "<<VC.first<<" , "<<VC.second<<endl;
	for(int i = 0;i<N;i++)
	{
		for(int j = i;j<N;j++)
		{
			double x = (P[i].first + P[j].first)/2.0;
			double y = (P[i].second + P[j].second)/2.0;
			double pend = Pendiente(VC,pair<double,double>({x,y}));
			double dpend = Pendiente(P[i],P[j]);
			if(pend * dpend != -1)
			{
			//	used[j] = true;
				pair<double,double> par = {pend,dpend};
				Cont[par]+= (1+(i!=j));
				if(Cont[par] == N)	
				{
					printf("Y\n");
					return true;
				}
				//if(j!=i)
				//	j = N;
			}
			//cout<<i<<" , "<<j<<" = "<<pend<<" , "<<dpend<<endl;
		}
	}
	printf("N\n");
	return true;
			
	
}
int main(int argc, char **argv)
{
	while(Caso());
	return 0;
}

