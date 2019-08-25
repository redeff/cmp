/*
 * ProblemaG.cxx
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
#include <map>
#include <cstring>
using namespace std;
typedef long long intl;
string pref(string s)
{
	string r;
	for(intl i = 0;s[i]!='-';i++)r+=s[i];
	return r;
}
string subf(string s)
{
	string r;
	for(intl i = s.size()-1;s[i]!='-';i--)r+=s[i];
	reverse(r.begin(),r.end());
	return r;
}
map<string,intl> vals;
intl Pref[2001],Subf[2001], VP[2001], Adj[2001][2001], Adj2[2001][2001];
string inp[2001];
intl CalcV(string s)
{
	intl ini = 0,fin = s.size()-1;
	while(s[ini]!='-')ini++;
	ini++;
	while(s[fin]!='-')fin--;
	if(ini>fin)return 0;
	string r;
	intl acum = 0;
	for(int i = ini;i<=fin;i++)
	{
		if(s[i] == '-')
		{
			if(vals[r] == 0) return intl(-1e9);
			acum += vals[r];
			r = "";
		}
		else
			r += s[i];
	}
	return acum;
}
bool Caso()
{
	intl G,P;
	cin>>G>>P;
	if(G == -1) return false;
	//memset(Pref,0,sizeof(Pref));
	//memset(Subf,0,sizeof(Subf));
	//memset(Adj,0,sizeof(Adj));
	//memset(VP,0,sizeof(VP));
	vals.clear();
	for(intl i = 0;i<G;i++)
	{
		string s;
		intl v;
		cin>>s>>v;
		vals[s] = max(vals[s], v);
	}
	intl R = 0;
	for(intl i = 0;i<P;i++)
	{
		string s;
		intl c;
		cin>>s>>c;
		inp[i] = s;
		Pref[i] = vals[pref(s)];
		Subf[i] = vals[subf(s)];
		VP[i] = CalcV(s) - c;
		if(Pref[i] && Subf[i] && CalcV(s) >= 0)
		{
			R = max(R,Pref[i] + Subf[i] + VP[i]);
		}
	//	cout<<s<<" tiene "<<Pref[i]<<" , "<<Subf[i]<<" , "<<VP[i]<<endl;
	}
	for(intl a = 0;a<P;a++)
		for(intl b = 0;b<P;b++)
		{
			string suba = subf(inp[a]);
			string preb = pref(inp[b]);
			string con = suba + preb;
			if(vals[con] == 0)
				Adj[a][b] = -1e12;
			else
				Adj[a][b] = vals[con] + VP[b];
		}
	for(intl v = 0;v<10;v++)
	for(intl k = 0;k<P;k++)
		for(intl i = 0;i<P;i++)
			for(intl j = 0;j<P;j++)
				if(VP[k] > -1e9 && Adj[i][j] < Adj[i][k] + Adj[k][j])
					Adj[i][j] = Adj[i][k] + Adj[k][j];
	for(intl i = 0;i<P;i++)
		for(intl j = 0;j<P;j++)
			Adj2[i][j] = Adj[i][j];
	for(intl v = 0;v<10;v++)
		for(intl k = 0;k<P;k++)
			for(intl i = 0;i<P;i++)
				for(intl j = 0;j<P;j++)
					if(VP[k] > -1e9 &&  Adj2[i][j] < Adj2[i][k] + Adj2[k][j])
						Adj2[i][j] = Adj2[i][k] + Adj2[k][j];
	
	for(intl a = 0;a<P;a++)
	{
		//cout<<endl;
		for(intl b = 0;b<P;b++)
		{
			//cout<<Adj[a][b]<<" "<<Adj2[a][b];
			if(VP[a] > -1e9 && VP[b] > -1e9 && Pref[a] && Subf[b])
			{
				if(Adj[a][b] < Adj2[a][b] && Adj2[a][b] > -1e9)
				{
					cout<<"*"<<endl;
					return true;
				}
				intl gan = Pref[a] + VP[a] + Subf[b] + Adj[a][b];
				R = max(R,gan);
			}
		}
	}
	cout<<R<<endl;
	return true;
}
int main(int argc, char **argv)
{
	while(Caso());
	return 0;
}
/*
 4 6
hola 5
como 5
les 3
va 2
como-co 3
mo-co 8
mo-les 4
como-como-les 12
ta-no-sirven 100
hasta-es 200
2 3
xyz 1000
zyxxyz 1000
xyz-zyx 1
zyx-xyz 1
xyz-xyz-zyx-xyz 1
2 1
abc 1
abcabc 1000
abc-abc 999
1 1
ser 10
no-ser 5
-1 -1
*/

