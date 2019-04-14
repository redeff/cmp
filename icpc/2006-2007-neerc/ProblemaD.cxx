/*
 * ProblemaD.cxx
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
#include <vector>
#define ll long long 
using namespace std;
map<string,vector<int> > palabras;
vector<vector<vector<int> > > AryC;
vector<vector<int> > > sentences;
vector<vector<pair<pair<int,int>,int> > > AryP, AryS;
string in;
int N,M,K;
int main(int argc, char **argv)
{
	cin>>N>>M>>K;
	for(int i = 0;i<N;i++)
	{
		string s;
		cin>>s;
		int ki;
		cin>>ki;
		vector<int> r;
		for(int j = 0;j<ki;j++)
		{
			int a;
			cin>>a;
			r.push_back(a);
		}
		palabras[s] = r;
	}
	sentences.resize(M);
	for(int i = 0;i<M;i++)
	{
		int l;
		cin>>l;
		for(int j = 0;j<l;j++)
		{
			int b;
			cin>>b;
			sentence[i].push_back(b);
		}
	}
	cin>>in;
	int L = in.size();
	AryP.resize(L), AryS.resize(L),AryC.resize(L);
	for(int i = 0;i<L;i++)
	{
		string s ="";
		AryC[i].resize(K+1);
		for(int j = i;j<L && j-i < 20;j++)
		{
			s += in[j];
			for(auto k : palabras[s])
				AryP.push_back({{i,j},k}), AryC[i][k].push_back(j);
		}
	}
	
	return 0;
}

