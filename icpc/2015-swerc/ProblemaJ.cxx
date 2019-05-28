/*
 * ProblemaJ.cxx
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
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")


#include <iostream>
#include <set>
#include <vector>
#define ll long long
using namespace std;
vector <double> gauss(vector <vector <double> > v,vector <double> v1){
	int n=v.size();
	vector <double> ans(m,0);
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n,;j++){
			if(v[i][j]!=0){
				double k=v[i][j]/v[i][i];
				for(int l=0;l<n;l++){
					v[l][j]-=v[l][i]*k;
				}
			}
		}
	}
	
	
	return ans;
} 
bool Caso()
{
	ll d1[3],d2[3],d3[3], d4[3];
	for(int i = 0;i<3;i++)
		cin>>d1[i];
	if(d1[0] == 0 && d1[1] == 0 && d1[2] == 0)
		return false;
	for(int i = 0;i<3;i++)
		cin>>d2[i];
	for(int i = 0;i<3;i++)
		cin>>d3[i];
	for(int i = 0;i<3;i++)
	{
		cin>>d4[i];
		d4[i] *= 10000;
	}
	for(int p1 = 1;p1<9999;p1++)
		for(int p2 = 1;p2<10000-p1;p2++)
		{
			ll p3 = 10000-p1-p2;
			if(d4[0] == p1 * d1[0] + p2 * d2[0] + p3 * d3[0] &&
				d4[1] == p1 * d1[1] + p2 * d2[1] + p3 * d3[1] &&
				d4[2] == p1 * d1[2] + p2 * d2[2] + p3 * d3[2])
			{
				cout<<"YES"<<endl;
				return true;
			}
		}
	cout<<"NO"<<endl;
	return true;
}
int main(int argc, char **argv)
{
	while(Caso());
	return 0;
}

