/*
 * ProblemaG.cxx
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
#include <algorithm>

using namespace std;

struct sensor{
	int a,b;
	long long w;
};
bool Compare(const sensor & a, const sensor & b)
{
	return a.w < b.w;
}
int CV[(350*351)/2 + 10][352],n,m;
sensor in[(350*351)/2 + 10];
bool Valido(int pos, int fin)
{
	int c1 = 0;
	for(int i = 0;i<n;i++)
		if(CV[pos-1][i] == CV[fin][i])
			return false;
		else if(CV[pos-1][i]+1 == CV[fin][i])
		{
			c1++;
			if(c1 > 2)
				return false;
		}
	return true;
}
int Binary(int pos)
{
	int fin = m+1, ini = pos;
	if(!Valido(pos,m))
		return -1;
	while(fin-ini>1)
	{
		int mid = (fin+ini)/2;
		if(Valido(pos,mid))
			fin = mid;
		else
			ini = mid;
	}
	if(Valido(pos,ini))
		return ini;
	return fin;
}
bool Caso()
{
	scanf("%d",&n);
	if(n == 0)
		return false;
	scanf("%d",&m);
	for(int i = 1;i<=m;i++)
		scanf("%d %d %lld",&in[i].a,&in[i].b,&in[i].w);
	sort(in+1,in+m+1,Compare);
	for(int i = 0;i<n;i++)
		CV[0][i] = 0;
	long long mindif = 1e18;
	for(int i = 1;i<=m;i++)
	{
		for(int j = 0;j<n;j++)
			CV[i][j] = CV[i-1][j];
		CV[i][in[i].a]++;
		CV[i][in[i].b]++;
	}
	for(int i = 1;i<=m;i++)
	{
		int fin = Binary(i);
		if(fin > -1)
		{
			long long d = in[fin].w - in[i].w;
			mindif = min(mindif,d);
		}
	}
	printf("%lld\n",mindif);
	return true;
}
int main(int argc, char **argv)
{
	while(Caso());
}

