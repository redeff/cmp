/*
 * ProblemaC.cxx
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
#include <cstring>
using namespace std;
int mata[1000][1000],matb[1000][1000], auxa = 0, auxb;
void Caso(int n)
{
	for(int i = 0;i<n;i++)
		for(int j = 0;j<n;j++)
			scanf("%d",&mata[i][j]), matb[j][i] = mata[i][j];
	bool R = true;
	for(int i = 0;i<n;i++)
		for(int j = 0;j<n;j++)
		{
			scanf("%d",&auxb);
			auxa = 0;
			
			for(int k = 0;k<n;k++)
				auxa += mata[i][k]*matb[j][k];
			//cout<<i<<" - "<<j<<" : "<<auxa<<" vs "<<auxb<<endl;
			if(auxa != auxb)
				R = false;
		}
	if(R)
		printf("YES");
	else
		printf("NO");
}
int main(int argc, char **argv)
{
	int n;
	scanf("%d",&n);
	while(n>0)
	{
		Caso(n);
		scanf("%d",&n);
		if(n > 0)
			printf("\n");
	}
}

