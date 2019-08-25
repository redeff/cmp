/*
 * ProblemaA.cxx
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
#include <map>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;
pair<int,int> puntos[2000];
typedef long long intl;
intl gcd(intl a, intl b)
{
	if(b == 0) return a;
	return gcd(b,a%b);
}
struct fract{
	intl a,b;
	
	void Normalizar()
	{
		intl g = gcd(a,b);
		a/=g;
		b/=g;
	}	
};
bool operator<(const fract & fa, const fract & fb)
	{
		return fa.a*fb.b < fb.a*fa.b;
	}
fract Sumar(fract A, fract B)
{
	A.a*=B.b;
	B.a*=A.b;
	A.b*=B.b;
	A.a+=B.a;
	A.Normalizar();
	return A;
}
fract Negar(fract A)
{
	A.a *= -1;
	return A;
}
map<fract,set<int> > cam;
set<int> res;
int main(int argc, char **argv)
{
	int N;
	cin>>N;
	//vector<string> graf (10,string(10,'.'));
	for(int i = 0;i<N;i++)
	{
		cin>>puntos[i].first>>puntos[i].second;
	//	graf[10-1-puntos[i].second][puntos[i].first] = '*';
	}
	//for(auto k : graf)cout<<k<<endl;
	//cout<<endl;
	for(int i = 0;i<N;i++)
	{
		for(int j = 0;j<N;j++)
		{
			if(puntos[i].second < puntos[j].second)
			{
				intl iy = puntos[i].second, ix = puntos[i].first;
				intl jy = puntos[j].second, jx = puntos[j].first;
				intl dx = -jx+ix;
				intl dy = jy-iy;
				fract P;
				P.a = dx * jy + jx*dy;
				P.b = dy;
				P.Normalizar();
				cam[P].insert(j);
			}
		}
	}
	res.insert(0);
	for(auto k : cam) 
	{
		//cout<<"En "<<k.first.a<<" / "<<k.first.b<<" se tapan : ";
		//for(auto j : k.second)cout<<j<<" ";
		//cout<<endl;
		res.insert(k.second.size());
	}
	cout<<res.size()<<endl;
	return 0;
}

