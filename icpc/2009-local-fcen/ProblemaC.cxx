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
#include <cmath>
using namespace std;
pair<double,double> in[4000];
double dist(pair<double,double> a, pair<double,double> b)
{
	double x = a.first - b.first, y = a.second - b.second;
	return (x*x + y*y);
}
double Caso(int n)
{
	for(int i = 0;i<n;i++)
	{
		cin>>in[i].first>>in[i].second;
	}
	double mind = 1e18;
	pair<double,double> most[2];
	for(int i = 0;i<n;i++)
	{
		int j = 0, k = 1;
		if(i == 0)
			j = 2;
		if(i == 1)
			k = 2;
		double d1 = dist(in[j],in[i]), d2 = dist(in[k],in[i]), d3;
		if(d1 > d2)
			most[0] = in[k], most[1] = in[j];
		else
			most[0] = in[j], most[1] = in[k];
		for(int l = max(j,k) + 1; l < n;l++)
		{
			if(l!=i)
			{
				d1 = dist(in[l],in[i]), d2 = dist(most[0],in[i]), d3 = dist(most[1],in[i]);
				if(d1 < d2)
					most[1] = most[0], most[0] = in[l];
				else if(d1 < d3)
					most[1] = in[l];
			}
		}
		d1 = dist(most[0],in[i]), d2 = dist(most[1],in[i]), d3 = dist(most[0],most[1]);
		double D =  sqrt(d1) + sqrt(d2) + sqrt(d3);
		if(D < mind)
			mind = D;
	}
	return mind;
}
int main(int argc, char **argv)
{
	int N;
	cin>>N;
	cout.precision(101);
	while(N!=-1)
	{
		cout<<Caso(N)<<endl;
		cin>>N;
	}
}

