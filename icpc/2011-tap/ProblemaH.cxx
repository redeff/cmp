/*
 * ProblemaH.cxx
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
#include <cstdio>
using namespace std;

struct nodo{
	double x, y, F;
	bool visto = false;
	void Input(double _x, double _y, double _F)
	{
		x = _x, y = _y, F = _F;
	}
};
double Abss(double x)
{
	if(x < 0)
		return -x;
	return x;
}
double raiz(double x)
{
	double r = 0.1;
	for(int i = 0;i<50;i++)
		r = (r+x/r)/2;
	//cout<<r<<" es raiz de "<<x<<endl;
	return r;
}
double Dist(nodo A, nodo B)
{
	//cout<<A.x<<" ; "<<A.y<<" vs "<<B.x<<" ; "<<B.y<<endl;
	double dx = A.x - B.x, dy = A.y - B.y;
	double d = raiz(dx*dx + dy*dy);
	//cout<<dx<<" - "<<dy<<" = "<<d<<" ; "<<A.F<<endl;
	return Abss(d - A.F);
}
int BuscarMin(vector<double> & dist, vector<nodo> & grafo)
{
	int i = 0, r = 0;
	while(grafo[i].visto && i<grafo.size())
		i++,r++;
	if(i == grafo.size())
		return -1;
	while(i < grafo.size())
	{
		if(dist[i] < dist[r] && grafo[i].visto == false)
			r = i;
		i++;
	}
	return r;
}
bool Caso()
{
	double Ix, Iy, Fx,Fy;
	int N;
	cin>>N>>Ix>>Iy>>Fx>>Fy;
	if(N == -1)
		return false;
	vector<nodo> grafo(N+2);
	vector<double> dist(N+2,1e16);
	dist[0] = 0;
	grafo[0].Input(Ix,Iy,0);
	grafo[N+1].Input(Fx,Fy,0);
	for(int i = 1;i<=N;i++)
	{
		double x,y,F;
		cin>>x>>y>>F;
		grafo[i].Input(x,y,F);
	}
	int next = 0;
	while((next=BuscarMin(dist,grafo))!=-1)
	{
		//cout<<next<<" : "<<dist[next]<<endl;
		grafo[next].visto = true;
		for(int i = 0;i<=N+1;i++)
		{
			double ld = Dist(grafo[next],grafo[i]) + dist[next];
			//cout<<"Paso en "<<i<<" y genero "<<ld<<endl;
			if(dist[i] > ld)
			{
				dist[i] = ld;
				//cout<<i<<" : "<<dist[i]<<endl;
			}
		}
	}
	printf("%.2f\n",dist[N+1]);
	return true;
}
int main(int argc, char **argv)
{
	while(Caso());
}

