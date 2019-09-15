/*
 * ProblemaH.cxx
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
#include <algorithm>
using namespace std;
int ConvStoI(string s)
{
	int L = s.size();
	int r = 0;
	for(int i = 0;i<L;i++) r = r*10 + (s[i]-'0');
	return r;
}
string ConvItoS(int n)
{
	string res = "";
	if(n == 0) return "0";
	while(n>0)
	{
		res += (n%10 + '0');
		n/=10;
	}
	reverse(res.begin(),res.end());
	return res;
}
int Caso(int num)
{
	int cp = 0;
	while(num != 0)
	{
		string ns = ConvItoS(num);
		sort(ns.begin(),ns.end());
		//cout<<num<<" - "<<ns<<endl;
		num -= ConvStoI(ns);
		cp++;
	}
	return cp;
}
int main(int argc, char **argv)
{
	int num = 0;
	while(cin>>num) cout<<Caso(num)<<endl;
	return 0;
}

