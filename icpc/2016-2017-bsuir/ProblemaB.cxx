/*
 * ProblemaB.cxx
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
using namespace std;
typedef long long ll;
string Caso(ll a, ll b)
{
	if(b == 1 && a == 1)
		return "";
	if(b>a/2)
		return Caso(a,a-b) +"1";
	else
		return Caso(a/2,b) + "0";
}
int main(int argc, char **argv)
{
	ll a,b;
	cin>>b>>a;
	a = ((ll)1)<<a;
	cout<<Caso(a,b)<<endl;
	return 0;
}

