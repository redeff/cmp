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
#define ll long long
using namespace std;
char F(ll n, ll m)
{
	
	if(n * 37 == m * 1000)
		return 'Y';
	else
		return 'N';
}
int main(int argc, char **argv)
{
	int n,m;
	cin>>n>>m;
	while(n!=-1 && m!=-1)
	{
		cout<<F(n,m)<<endl;
		cin>>n>>m;
	}
	return 0;
}

