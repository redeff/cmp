/*
 * Problema E.cxx
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
#include <vector>

using namespace std;
string in[200];
const int dif = 'Z'-'A'+11;
pair<int,string> DP[200][dif];
void Case(int N, int M, int Cn)
{
	for(int i = 1;i<=M;i++)
	{
		cin>>in[i];
		//cout<<"Dia "<<i<<" = "<<in[i]<<endl;
		for(int k = 0;k<dif;k++)
			DP[i][k] = {1000000,""};
	}
	int ini,fin;
	cin>>ini>>fin;
	//cout<<ini<<" - "<<fin<<endl;
	for(int i = 0;i<dif;i++)
	{
		DP[ini][i].first = 0;
		DP[ini][i].second = "";
		//DP[ini][i].second += char('A'+i);
	}
	for(int i = ini;i<fin;i++)
	{
		for(int j = 0;j<N;j++)
		{
			//cout<<i<<" - "<<j<<" - "<<in[i][j]<<endl;
			if(in[i][j] != 'X')
			{
				DP[i][j].second += char('A' + j);
			//	cout<<DP[i][j].first<<" - "<<DP[i][j].second<<endl;
				if(DP[i+1][j] > DP[i][j])
					DP[i+1][j] = DP[i][j];
				DP[i][j].first ++;
				for(int k = 0;k<N;k++)
				{
					if(DP[i][j]< DP[i+1][k])
						DP[i+1][k] = DP[i][j];
				}
			}
		} 
	}
	pair<int,string> res = DP[fin][0];
	for(int i = 1;i<N;i++)
		if(DP[fin][i] < res)
			res = DP[fin][i];
	cout<<"Case "<<Cn<<":"<<endl<<endl;
	if(res.first == 1000000)
	{
		cout<<"Not available"<<endl;
		return;
	}
	vector<pair<int,char> > postr;
	string sres = res.second;
	char c = sres[0];
	int cant = 0;
	for(auto k : sres)
	{
		if(k == c)
			cant++;
		else
			postr.push_back({cant,c}),cant = 1, c = k;
	}
	postr.push_back({cant,c});
	for(auto k : postr)
	{
		cout<<k.second<<": "<<ini;
		ini += k.first;
		cout<<"-"<<ini<<endl;
	}
}
int main(int argc, char **argv)
{
	int N,M,i = 1;
	cin>>M>>N;
	while(N && M)
	{
		Case(N,M,i),i++;
		cin>>M>>N;
	    if(M&&N)
			cout<<endl;
	}
}

