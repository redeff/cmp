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
#include <map>
#include <cstring>
using namespace std;
int dp[212][212][212], in[212];
int Caso(int N)
{
	map<int,int> mapa;
	for(int i = 0;i<N;i++)
	{
		cin>>in[i];
		mapa[in[i]] = -1;
	}
	int val = 2;
	for(auto & k : mapa)
	{
		k.second = val;
		val++;
	}
	memset(dp,0,sizeof(dp));
	int maxr = 0;
	for(int i = 0;i<N;i++)
	{
		int v = mapa[in[i]];
		for(int w = 0;w<=210;w++)
			for(int b = 0;b<=210;b++)
			{
				if(dp[i+1][w][b] < dp[i][w][b])
					dp[i+1][w][b] = dp[i][w][b];
				if(w > v && dp[i+1][v][b] < dp[i][w][b]+1)
					dp[i+1][v][b] = dp[i][w][b]+1, maxr = max(maxr,dp[i][w][b]+1);
				if(b < v && dp[i+1][w][v] < dp[i][w][b]+1)
					dp[i+1][w][v] = dp[i][w][b]+1, maxr = max(maxr,dp[i][w][b]+1);
			}
	}
	return maxr;
}
int main(int argc, char **argv)
{
	int N;
	cin>>N;
	while(N!=-1)
	{
		int r = Caso(N);
		cout<<N-r<<endl;
		cin>>N;
	}
}

