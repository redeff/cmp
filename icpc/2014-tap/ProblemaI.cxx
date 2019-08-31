/*
 * ProblemaI.cxx
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
#include <vector>
using namespace std;
typedef long long intl;
int main(int argc, char **argv)
{
	intl lim = 1e7 + 2;
	vector<bool> Criba(lim, true);
	vector<int> p;
	
	for(intl i = 2;i<lim;i++)
	{
		if(Criba[i])
		{
			p.push_back(i);
			for(intl j = i*i;j<lim;j+=i)
				Criba[j] = false;
		}
	}
	intl S = 0;
	for(int i = 0;i<intl(p.size())-1;i++)
		S+=(p[i+1]-p[i])*(p[i+1]-p[i]);
	cout<<S<<endl;
	return 0;
}

