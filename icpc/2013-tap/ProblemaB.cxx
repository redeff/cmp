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
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char **argv)
{
	int N, T = 0;
	cin>>N;
	vector<int> votos(N);	
	for(int i = 0;i<N;i++){cin>>votos[i];T+=votos[i];}
	sort(votos.begin(),votos.end());
	int m1 = votos.back(), m2 = votos[votos.size()-2];
	int d = m1-m2;
	if(d > 0 && (m1*20 >= T*9 || m1 * 5 >= T*2 && d*10 >= T))
	{
		cout<<1<<endl;
		return 0;
	}
	cout<<2<<endl;
	return 0;
}

