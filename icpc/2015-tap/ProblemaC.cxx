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
using namespace std;
void Caso(int N)
{
	int S, J, D;
	string g;
	cin>>S>>J>>D>>g;
	int gA = 0, gB = 0, sA = 0, sB = 0;
	for(auto k : g)
	{
		if(k == 'A')
		{
			sA++;
			if(sA > sB && sA - sB >= D && sA >= J)
				gA++, sA = 0, sB = 0;
		}
		else
		{
			sB++;
			if(sB > sA && sB - sA >= D && sB >= J)
				gB++, sA = 0, sB = 0;
		}
	}
	cout<<gA<<" "<<gB<<endl;
}
int main(int argc, char **argv)
{
	int N;
	while(cin>>N)Caso(N);
	return 0;
}
/*
10 5 2 1
AAAAAAAAAA
21 3 3 2
AABABBBABBBABABABBABB
*/
