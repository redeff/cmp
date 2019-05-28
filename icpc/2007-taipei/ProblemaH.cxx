/*
 * ProblemaH.cxx
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
#include <vector>
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
ll PROBAR(vector<pair<int,int> > & vx, vector<pair<int,int> > & vy, int x, int y)
{
	ll op1 = 0, op2 = 0;
	ll maxx = vx[x].first, maxy = vy[y].first;
	for(int i = 0;i<=x;i++)
	{
		op1 += vx[i].second;
		if(vx[i].second > maxy*2)
			op2 += vx[i].second-maxy*2;
	}
	for(int i = 0;i<=y;i++)
	{
		op2 += vy[i].second;
		if(vy[i].second > maxx*2)
			op1 += vy[i].second-maxx*2;
	}
	//cout<<"op1 : "<<op1<<" , op2 : "<<op2<<endl;
	return max(op1,op2);
}
void Caso(int nc)
{
	int X,Y;
	cin>>X>>Y;
	vector<pair<int,int> > vx, vy;
	vx = vy = {{0,0}};
	for(int i = 0;i<X;i++)
	{
		int p,g;
		scanf("%d %d",&p,&g);
		g-=p;
		if(g < 0)
			g = 0;
		vx.push_back({p,g});
	}
	for(int i = 0;i<Y;i++)
	{
		int p,g;
		scanf("%d %d",&p,&g);
		g-=p;
		if(g<0)
			g = 0;
		vy.push_back({p,g});
	}
	sort(vx.begin(),vx.end());
	sort(vy.begin(),vy.end());
	long long R = 0;
	for(int i = 0;i<=X;i++)
		for(int j = 0;j<=Y;j++)
		{
			R = max(R,PROBAR(vx,vy,i,j));
//			cout<<i<<" , "<<j<<" : " <<R<<endl;
		}
	cout<<"Case "<<nc<<": "<<R;
	int cero;
	cin>>cero;
}
int main(int argc, char **argv)
{
	int T;
	cin>>T;
	for(int i = 1;i<=T;i++)
	{
		Caso(i);
		//if(T-i)
			cout<<endl;
	}
	return 0;
}

