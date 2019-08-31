/*
 * ProblemaVerdaderoA.cxx
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
using namespace std;
int main(int argc, char **argv)
{
	int t;
	cin>>t;
	while(t--){
	
	int N;
	cin>>N;
	pair<int,char> c;
	cin>>c.first>>c.second;
	bool flag=0;
	for(int i = 1;i<N;i++)
	{
		pair<int,char> p;
		cin>>p.first>>p.second;
		if(p.first == c.first || p.second == c.second)
		{
			flag=1;
			
		}
		c = p;
	}
	if(flag){
		cout<<"M"<<endl;
	}
	else{
		cout<<"B"<<endl;
	}
	}
	return 0;
}

