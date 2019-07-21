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
#include <map>
#include <cstring>
#include <cstdio>
using namespace std;
int in[201], DP[210][220][220];
bool Caso()
{
	int N;
	cin>>N;
	if(N == -1)
		return false;
	memset(DP,0,sizeof(DP));
	map<int,int> mapa;
	for(int i = 0;i<N;i++)
	{
		scanf("%d",in+i);
		mapa[in[i]] = 0;
	}
	int v = 5;
	for(auto & k : mapa)
		k.second = v, v++;
	int maxP = 0;
	for(int i = 0;i<N;i++)
	{
		int n = mapa[in[i]];
		for(int j = 0;j<210;j++)
			for(int k = 0;k<210;k++)
			{
				DP[i+1][j][k] = max(DP[i][j][k],DP[i+1][j][k]), maxP = max(DP[i+1][j][k],maxP);
				if(j>n)
					DP[i+1][n][k] = max(DP[i+1][n][k],DP[i][j][k] + 1), maxP = max(DP[i+1][n][k],maxP);
				if(k<n)
					DP[i+1][j][n] = max(DP[i+1][j][n],DP[i][j][k] + 1), maxP = max(DP[i+1][j][n],maxP);
			}
	}
	printf("%d\n",(N-maxP));
	return true;
}

int main(int argc, char **argv)
{
	while(Caso());
	return 0;
}
/*
 * 8
1 4 2 3 3 2 4 1
12
7 8 1 2 4 6 3 5 2 1 8 7
-1
* */
