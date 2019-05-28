/*
 * ProblemaA.cxx
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
#include <algorithm>
using namespace std;
bool Caso()
{
	int x, y;
	double w;
	cin>>x>>y>>w;
	if(x == 0 && y == 0 && w == 0)
		return false;
	double sw = w/2.0;
	vector<double> vx,vy;
	for(int i = 0;i<x;i++)
	{
		double p;
		cin>>p;
		p-=sw;
		vx.push_back(p);
	}
	for(int i = 0;i<y;i++)
	{
		double p;
		cin>>p;
		p-=sw;
		vy.push_back(p);
	}
	vx.push_back(75), vy.push_back(100);
	sort(vx.begin(),vx.end());
	sort(vy.begin(),vy.end());
	double minx = 0, miny = 0;
	bool FailX = false, FailY = false;
	for(auto k : vx)
	{
		if(k > minx)
			FailX = true;//, cout<<"x falla en "<<k<<endl;
		minx = k+w;
	}
	for(auto k : vy)
	{
		if(k > miny)
			FailY = true;//, cout<<"falla en "<<k<<endl;
		miny = k+w;
	}
	if(FailX || FailY)
	{
		cout<<"NO"<<endl;
	}
	else
	{
		cout<<"YES"<<endl;
	}
	return true;
}
int main(int argc, char **argv)
{
	cin.precision(7);
	while(Caso());
	return 0;
}

