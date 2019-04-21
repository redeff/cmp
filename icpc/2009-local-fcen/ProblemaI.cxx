/*
 * ProblemaI.cxx
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
#include <map>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;
string inversion(string & s, int i, int j)
{
	string a = s.substr(0,i);
	string b = s.substr(i,j-i);
	reverse(b.begin(),b.end());
	string c = "";
	if(j < 10)
		 c = s.substr(j,10-j);
	return a+b+c;
}
unordered_map<string,int> dist;
int Caso(string C)
{
	//map<string,int> dist;
	dist[C] = 1;
	queue<pair<string,int> > Q;
	Q.push({C,1});
	while(Q.size())
	{
		pair<string,int> p = Q.front();
		Q.pop();
		//cout<<p.first<<" == "<<p.second<<endl;
		//cout<<p.first<<endl;
		//if(p.first == D)
		//	return p.second-1;
		int c = p.second + 1;
		for(int i = 0;i<10;i++)
			for(int j = i+1; j <= 10;j++)
			{
				string sig = inversion(p.first,i,j);
				if(dist[sig] == 0)
				{
					//if(dist.size()%10000 == 0)
					//	cout<<sig<<" tiene dist "<<dist[sig]<<">> "<<dist.size()<<endl;
				
					dist[sig] = c;
					Q.push({sig,c});
				}
			}
	}
	return 0;
}
char cambio[255];
int TCaso(string C, string D)
{
	for(int i = 0;i<10;i++)
	{
		cambio[C[i]] = 'a'+i;
	}
	for(int i = 0;i<10;i++)
	{
		C[i] = cambio[C[i]];
		D[i] = cambio[D[i]];
	}
	return dist[D]-1;
}
int main(int argc, char **argv)
{
	string C,D;
	cin>>C>>D;
	Caso("abcdefghij");
	//cout<<"k"<<endl;
	while(C!="*")
	{
		cout<<TCaso(C,D)<<endl;
		cin>>C>>D;
	}
}

