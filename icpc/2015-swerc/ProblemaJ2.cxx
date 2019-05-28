/*
 * ProblemaJ2.cxx
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
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#define ll long long
using namespace std;
struct punto{
	ll x, y;
	void Leer()
	{
	//	cin>>x>>y;
		scanf("%lld %lld",&x,&y);
	}
};
punto operator-(punto a, punto b)
{
	punto c;
	c.x = a.x-b.x;
	c.y = a.y-b.y;
	return c;
}
punto operator+(punto a, punto b)
{
	punto c;
	c.x = a.x+b.x;
	c.y = a.y+b.y;
	return c;
}

ll Cruz(punto a, punto b)
{
//	cout<<"Operación Cruz entre "<<a.x<<" , "<<a.y<<" y "<<b.x<<" , "<<b.y<<" = ";
//	cout<<a.x * b.y - a.y*b.x<<endl;
	return a.x * b.y - a.y*b.x;
}
bool operator==(punto a, punto b)
{
	return (a.x == b.x) && (a.y == b.y);
}
ll abss(ll x)
{
	if(x < 0)
		return -x;
	return x;
}
/// Si el producto cruz de 2 vectores es negativo, el segundo tiene mayor angulo
punto Vertice;
bool OrdenAngulo(const punto & a, const punto & b)
{
	if(a == Vertice)
		return true;
	if(b == Vertice)
		return false;
	punto ra = a-Vertice, rb = b-Vertice;
	return Cruz(ra,rb) > 0;
}
int L,S;
punto Grandes[100000], Chicos[100000];
vector<punto> Convex;
bool operator<(punto a, punto b)
{
	if(a.x == b.x)
		return a.y<b.y;
	return a.x<b.x;
}
bool BusquedaBinaria(punto p)
{
	int Cl = Convex.size();
	int a = 0, b = Cl-2;
	vector<punto> v;
	if(Cl > 4)
	{
		while(b-a > 1)
		{
			int m = (b+a)/2;
			if(Cruz(Convex[m]-Vertice,p-Vertice)<0)
				b = m;
			else
				a = m;
		}
		v = {Vertice,Convex[a],Convex[b],Vertice};
	}
	else
		v = Convex;
	//cout<<v[1].x<<" y "<<v[1].y<<" || "<<v[2].x<<" y "<<v[2].y<<endl;
	punto p1 = v[1]-Vertice, p2 = v[2] -Vertice;
	//cout<<" = "<<p1.x<<" , "<<p1.y<<" || "<<p2.x<<" , "<<p2.y<<endl;
	ll pArea = 0, Area = abss(Cruz(v[1]-Vertice,v[2]-Vertice));
	
	for(int i = 0;i<3;i++)
	{
		pArea += abss(Cruz(v[i]-p,v[i+1]-p));
	}
	//cout<<"Punto "<<p.x<<" , "<<p.y<<" : "<<pArea<<" vs "<<Area<<endl;
	return pArea == Area;
}
int main(int argc, char **argv)
{
	cin>>L;
	set<punto> grande;
	for(int i = 0;i<L;i++)
	{
		Grandes[i].Leer();
		grande.insert(Grandes[i]);
		if(i == 0 || Grandes[i].y < Vertice.y || (Grandes[i].y == Vertice.y && Grandes[i].x < Vertice.x))
			Vertice = Grandes[i];
	}
	sort(Grandes,Grandes+L,OrdenAngulo);
	Convex.push_back(Grandes[0]);
	Convex.push_back(Grandes[1]);
	//for(int i = 0;i<L;i++)
	//	cout<<"Grandes[ "<<i<<" ] = "<<Grandes[i].x<<" , "<<Grandes[i].y<<endl;
		
	for(int i = 2;i<L;i++)
	{
		bool sacar = true;
		while(Convex.size() > 2 && sacar)
		{
			sacar = false;
			punto b = Convex.back();
			punto a = Grandes[i];
			punto c = Convex[Convex.size()-2];
			punto ra = a-c, rb = b-c;
			if(Cruz(ra,rb) > 0)
			{
				Convex.pop_back();
				sacar = true;
			}
		}
		Convex.push_back(Grandes[i]);
	}
	//cout<<Convex.size()<<endl;
	int Cl = Convex.size();
	Convex.push_back(Convex[0]);
	ll Area = 0;
	for(int i = 1;i<Cl-1;i++)
		Area += abss(Cruz(Convex[i]-Convex[0],Convex[i+1]-Convex[0]));
	cin>>S;
	int R = 0;
	for(int i = 0;i<S;i++)
	{
		punto s;
		s.Leer();
		ll sArea = 0;
	
		//for(int j = 0;j<Cl;j++)
		//	sArea += abss(Cruz(Convex[j]-s,Convex[j+1]-s));
		//cout<<i<<"( "<<s.x<<" , "<<s.y<<" ) = "<<sArea<<" vs "<<Area<<endl;
		if(grande.count(s) >= 1)
			R++;
		else
			R += BusquedaBinaria(s);
		//R += (sArea == Area);
	}
	//for(int i = 0;i<Cl;i++)
	//	cout<<Grandes[i].x<<" - "<<Grandes[i].y<<endl;
	cout<<R;
}

