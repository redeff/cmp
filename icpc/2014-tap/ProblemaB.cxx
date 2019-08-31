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
intl sec;
intl p3[20];
string res[1001];
void Num(string num, intl v)
{
	//cout<<num<<" = "<<v<<endl;
	int p = num.size();
	if(v > 0 && v <= 1000 && num.size() && num[0] != '0') res[v] = num; 
	if(p == 13) return;
	Num("0"+num,v);
	Num("+"+num,v+p3[p]);
	Num("-"+num,v-p3[p]);
}
int main(int argc, char **argv)
{
	p3[0] = 1;
	for(int i = 1;i<20;i++)
		p3[i] = p3[i-1] * 3;
	res[0] = "0";
	Num("",0);
	int T;
	cin>>T;
	for(int i = 0;i<T;i++)
	{
		int val;
		cin>>val;
		cout<<res[val]<<endl;
	}
	return 0;
}

