/*
 * ProblemaF.cxx
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
#include <cstdio>
#include <map>
#include <vector>
using namespace std;
struct carta{
	string palo;
	int num;
	void Leer()
	{
		cin>>num>>palo;
	}
};
int valor[13];
int Actual(vector<int> v)
{
	if(v.size() == 0)
		return 0;
	if(v.size() == 1)
		return v[0];
	if(v.size() == 2)
		return v[0] + v[1] + 20;
	return 20 + max(v[0]+v[1],max(v[0]+v[2],v[1]+v[2]));
}
int Maximo(vector<int> v)
{
	if(v.size() == 0)
		return 7;
	int maxV = 0;
	for(auto k : v)
		maxV = max(k,maxV);
	int add = 7;
	if(maxV == 7)
		add = 6;
	return 20 + maxV + add;
}
bool Caso()
{
	carta mano[3];
	map<string,vector<int> > ENV;
	for(int i = 0;i<3;i++)
	{
		
		string s;
		int num;
		cin>>num>>s;
		if(num == -1)
			return false;
		
		//mano[i].Leer();
		ENV[s].push_back(valor[num]);
	}
	int ACT = 0, MAX = 0;
	for(auto j : ENV)
		ACT = max(ACT,Actual(j.second)), MAX = max(MAX,Maximo(j.second));
	cout<<(MAX-ACT)<<endl;
	return true;
	
}
int main(int argc, char **argv)
{
	for(int i = 1;i<=7;i++)
		valor[i] = i;
	while(Caso());
	return 0;
}

