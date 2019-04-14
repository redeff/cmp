/*
 * ProblemaC.cxx
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
#include <queue>
#include <vector>
#include <cmath>
#define ll long long 
using namespace std;

struct pos{
	ll piso,x,y;
	void Leer()
	{
		cin>>piso>>x>>y;
	}
};
double Euclides(pos a, pos b)
{
	ll dz = (a.piso-b.piso)*5, dy = a.y-b.y, dx = a.x-b.x;
	dz*=dz, dy *= dy, dx *= dx;
	return sqrt(double(dz+dx+dy));
	
}
pos input[2000];
void Dijstrak(int ini, int fin, vector<vector<pair<int,double> > > & Ary, int N)
{
	vector<double> dist(N,1e9);
	vector<int> pad(N,-1);
	dist[ini] = 0;
	priority_queue<pair<double,int>,vector<pair<double,int> >, greater<pair<double, int> > > PQ;
	PQ.push({0,ini});
	while(PQ.size())
	{
		auto p = PQ.top();
		PQ.pop();
		int n = p.second;
		double d = p.first;
		for(auto k : Ary[n])
		{
			double c = k.second + d;
			int next = k.first;
			if(c < dist[next])
				dist[next] = c, pad[next] = n, PQ.push({dist[next],next});
		}
	}
	vector<int> R;
	int pi = fin;
	while(pi!=-1)
	{
		R.push_back(pi);
		pi = pad[pi];
	}
	for(int i = R.size()-1;i>=0;i--)
	{
		cout<<R[i];
		if(i)
			cout<<" ";
	}
	cout<<endl;
}
void Caso(int N, int M)
{
//	cout<<N<<" y "<<M<<endl;
	vector<vector<pair<int,double> > > Ary(N);
	for(int i = 0;i<N;i++)
		input[i].Leer();
	for(int i = 0;i<M;i++)
	{
		int a,b;
		string forma;
		cin>>a>>b>>forma;
//		cout<<a<<" con "<<b<<" de "<<forma<<endl;
		if(forma == "walking" || forma == "stairs")
		{
			double dist = Euclides(input[a],input[b]);
			Ary[a].push_back({b,dist});
			Ary[b].push_back({a,dist});
		}
		if(forma == "lift")
		{
			Ary[a].push_back({b,1});
			Ary[b].push_back({a,1});
		}
		if(forma == "escalator")
		{
			double dist = Euclides(input[a],input[b]);
			Ary[a].push_back({b,1});
			Ary[b].push_back({a,3*dist});
		}
	}
	int Q;
	cin>>Q;
	for(int i = 0;i<Q;i++)
	{
		int ini,fin;
		cin>>ini>>fin;
		Dijstrak(ini,fin,Ary,N);
	}
}
int main(int argc, char **argv)
{
	int N,M;
	int t = 0;
	while(cin>>N>>M)
	{
		if(t>0)
			cout<<endl;
		Caso(N,M);
		t++;
	}
}

