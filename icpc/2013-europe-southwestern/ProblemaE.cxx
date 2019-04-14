/*
 * ProblemaE.cxx
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
#include <deque>
#include <set>
using namespace std;
vector<string> unidor(deque<string> dq)
{
	string r= dq[0];
	vector<string> vr;
	int L = dq.size();
	for(int i = 1;i<L;i++)
	{
		r = (r + " " + dq[i]);
		vr.push_back(r);
	}
	return vr;
}
string Normalizar(string s)
{
	for(auto & k : s)
	{
		if(k>='A' && k<='Z')
			k-=('A'-'a');
	}
	return s;
}
set<string> signos = {".",",",":",";","?","!"};
void Caso(int n, int nc)
{
	cout<<"Learning case "<<nc<<endl;
	set<string> conocido;
	string in;
	deque<string> dq;
	cin>>in;
	while(in!="*")
	{
		//Normalizar(in);
		if(signos.count(in))
		{
			dq = deque<string>(0);
		}
		else
		{
			conocido.insert(Normalizar(in));
			dq.push_back(in);
			if(dq.size() > n)
				dq.pop_front();
			vector<string> vr = unidor(dq);
			for(auto k : vr)
				conocido.insert(Normalizar(k));
			//conocido.insert(unidor(dq));
		}
		cin>>in;
	}
	dq = deque<string>(0);
	cin>>in;
	bool consultar = false;
	string sentencia="";
	conocido.insert("joe");
	while(in!="#")
	{
		//Normalizar(in);
		if(signos.count(in))
		{
			vector<string> vr = unidor(dq);
			//for(auto k : vr)
			if(consultar)
			{
				cout<<"What does the sentence \""<<sentencia<<"\" mean?"<<endl;
			}
			consultar = false;
			sentencia = "";
			dq = deque<string>(0);
		
		}
		else
		{
			//conocido.insert(in);
			if(conocido.count(Normalizar(in)) == 0)
			{
				cout<<"What does the word \""<<in<<"\" mean?"<<endl;
				conocido.insert(Normalizar(in));
			}
			dq.push_back(in);
			if(dq.size() > n)
				dq.pop_front();
			vector<string> vr = unidor(dq);
			for(auto k : vr)
			//		if(dq.size() == n)
			{
				//string k = vr.back();
				if(conocido.count(Normalizar(k)) == 0)
				{
					//cout<<"What does the sentence \""<<k<<"\" mean?"<<endl;
					consultar = true;
					//for(auto j : vr)
					conocido.insert(Normalizar(k));
				}
			}
			if(sentencia == "")
				sentencia = in;
			else
				sentencia = sentencia + " " + in;
			//	conocido.insert(k);
			//conocido.insert(unidor(dq));
		}
		cin>>in;
	}
//	cout<<endl;	
}
int main(int argc, char **argv)
{
	int nc = 1, N;
	while(cin>>N)
	{
		if(nc > 1)
			cout<<endl;
		Caso(N,nc), nc++;
	}
	
}

