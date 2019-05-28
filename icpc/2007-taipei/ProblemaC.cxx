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


#include <iostream>
#include <cstdio>
#include <vector>
#define ll long long
using namespace std;
struct camino
{
	long long cost;
	vector<int> steps;
};
bool operator<(const camino & a, const camino & b)
{
	if(a.cost != b.cost)
		return a.cost < b.cost;
	if(a.steps.size() != b.steps.size())
		return a.steps.size() < b.steps.size();
	return a.steps < b.steps;
}
ll xpos[2000];
camino best[2000];
void Caso(int n)
{
	xpos[0] = 0;
	for(int i = 1;i<=n;i++)
	{
		int a;
		scanf("%d",&a);
		best[i].cost = 0;
		xpos[i] = xpos[i-1] + a;
	}
	best[0].steps = {0};
	for(int i = 0;i<n;i++)
	{
		camino C = best[i];
		for(int j = i+1;j<=n;j++)
		{
			C.steps.push_back(j);
			ll b =(xpos[j]-xpos[i])-100;
			b*=b;
			C.cost+=b;
			if(C<best[j] || best[j].cost == 0)
				best[j] = C;
			C.cost-=b;
			C.steps.pop_back();
		}
	}
	camino C = best[n];
	cout<<"p="<<C.cost<<endl<<" ";
	int L = C.steps.size();
	for(int i = 1;i<=L;i++)
	{
		cout<<C.steps[i-1];
		if(i%30 == 0 && i!=L)
			cout<<endl<<" ";
		else if(i!=L)
			cout<<" ";
	}
	cout<<endl;
}
int main(int argc, char **argv)
{
	int k = 0,n;
	while(cin>>n)
	{
		if(k != 0 && n!= 0)
			cout<<endl;
		if(n == 0)
			break;
		Caso(n);
		k= 1000;
	}
	return 0;
}

