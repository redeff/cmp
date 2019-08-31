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
using namespace std;
typedef long long intl;
intl R = 0;
map<pair<int,int>,map<pair<int,int> ,intl> > cant;
pair<int,int> in[1001];
int gcd(int a, int b)
{
	if(b == 0) return a;
	return gcd(b,a%b);
}
int main(int argc, char **argv)
{
	int N;
	cin>>N;
	for(int i = 0;i<N;i++)
	{
		cin>>in[i].first>>in[i].second;
		for(int j = 0;j<i;j++)
		{
			pair<int,int> mid = {in[i].first + in[j].first, in[i].second + in[j].second};
			int dx = in[i].first - in[j].first;
			int dy = in[i].second - in[j].second;
			int g = gcd(dx,dy);
			dx/=g, dy/=g;
			cant[mid][{dx,dy}]++;
		}
	}
	for(auto & k : cant)
	{
		intl l = 0;
		for(auto j : k.second)
		{
			R += l*j.second;
			l += j.second;
		}
	}
	cout<<R<<endl;
	return 0;
}

