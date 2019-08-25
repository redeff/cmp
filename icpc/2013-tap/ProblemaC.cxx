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
using namespace std;
typedef long long intl;
intl CF[100001], Camino[100001];
int main(int argc, char **argv)
{
	int N,S;
	cin>>N>>S;
	vector<vector<int > > hijos(N+1);
	for(int i = 0;i<S;i++)
	{
		int a,b;
		cin>>a>>b;
		hijos[a].push_back(b);
	}
	CF[N] = Camino[N] = 1;
	for(int i = N-1;i>=1;i--)
	{
		CF[i] = Camino[i] = 0;
		for(auto j : hijos[i])
		{
			CF[i]+=CF[j];
			Camino[i] = max(Camino[i],Camino[j]);
		}
		Camino[i] += CF[i];
	}
	cout<<Camino[1]<<endl;
	
	return 0;
}

