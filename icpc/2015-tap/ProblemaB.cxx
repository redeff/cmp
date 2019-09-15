/*
 * ProblemaB.cxx
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
typedef long long intl;
bool Posible(intl L, intl K, intl m)
{
	intl acum = 0, cant = 0;
	for(intl i = 0;i<L;i++)
	{
		acum+=2*i+1;
		if(acum >= m)
			acum = 0, cant++;
	}
	return (cant>=K);
}
intl Caso(intl L, intl K)
{
	intl a = 0, b = L*L*2;
	while(b-a>1)
	{
		intl m = (b+a)/2;
		if(Posible(L,K,m)) a = m;
		else b = m;
	} 
	return a;
}
int main(int argc, char **argv)
{
	intl L,K;
	while(cin>>L>>K)cout<<Caso(L,K)<<endl;
	return 0;
}

