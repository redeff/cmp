/*
 * ProblemaA3.cxx
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
#include <cstring>
#include <vector>
using namespace std;
vector<int> cartas[2802][6];
int DP[152][2802];
void Caso()
{
	for(int j = 0;j<=1800;j++)
	{
		for(int i = 0;i<=5;i++)
			cartas[j][i].clear();
		for(int i = 0;i<=151;i++)
			DP[i][j] = -1;
	}
	int n;
	cin>>n;
	for(int i = 0;i<n;i++)
	{
		int v,nf;
		char c;
		cin>>v>>c>>nf;
		c-='A';
		cartas[v][c].push_back(nf);
	}
	string S;
	cin>>S;
	for(auto j : cartas[1][S[0]-'A'])
		{
			DP[1][j] = j;
		}
	int L = S.size();
	for(int i = 1;i<L;i++)
	{
		for(int j = 0;j<=1800;j++)
			if(DP[i][j] > -1)
				for(auto k : cartas[j][S[i]-'A'])
					DP[i+1][k] = max(DP[i][j]+k, DP[i+1][k]);
	}
	int R = 0;
	for(int i = 1;i<=1800;i++)
		R = max(R,DP[L][i]);
	cout<<R;
	
}
int main(int argc, char **argv)
{

	int T;
	cin>>T;
	while(T--)
	{
		Caso();
		//if(T>0)
			cout<<endl;
	}
	return 0;
}

