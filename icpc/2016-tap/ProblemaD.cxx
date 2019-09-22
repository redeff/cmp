/*
 * ProblemaD.cxx
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
#include <set>
#include <map>
using namespace std;
typedef long long intl;
intl gcd(intl a, intl b)
{
	if(b == 0) return a;
	return gcd(b,a%b);
}
struct fract{
	intl num,den;
	void Normalizar()
	{
		intl g = gcd(num,den);
		den/=g;
		num/=g;
	}
};
bool operator<(const fract & a, const fract & b)
{
	return a.num*b.den < b.num*a.den;
}
fract operator+(const fract & a, const fract & b)
{
	fract c;
	c.den = a.den * b.den;
	c.num = a.num*b.den + b.num*a.den;
	c.Normalizar();
	return c;
}
fract operator*(const fract & a, const fract & b)
{
	fract c;
	c.num = a.num*b.num;
	c.den = a.den*b.den;
	c.Normalizar();
	return c;
}
fract operator/(const fract & a, const fract & b)
{
	fract c;
	c.num = a.num * b.den;
	c.den = a.den * b.num;
	c.Normalizar();
	return c;
}
bool operator==(const fract & a, const fract & b)
{
	return a.num*b.den == b.num*a.den;
}
fract Dist(pair<intl,intl> A, pair<intl,intl> B)
{
	intl dy = A.first - B.first, dx = A.second - B.second;
	dy*=dy, dx*=dx;
	fract res;
	res.num = (dx+dy);
	res.den = 1;
	return res;
}
int Caso(int N)
{
	vector<map<fract,set<int> > > dist(N);
	vector<pair<intl,intl> > puntos;
	for(int i = 0;i<N;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		puntos.push_back({a,b});
		for(int j = 0;j<i;j++)
		{
			fract d = Dist(puntos[i],puntos[j]);
			dist[i][d].insert(j);
			dist[j][d].insert(i);
		}
	}
	vector<fract> lados;
	lados.push_back(Dist(puntos[0],puntos[1]));
	lados.push_back(Dist(puntos[0],puntos[2]));
	lados.push_back(Dist(puntos[1],puntos[2]));
	int numQ = 0;
	if(lados[0] == lados[1]) numQ++;
	if(lados[1] == lados[2]) numQ++;
	if(lados[0] == lados[2]) numQ++;
	int res = 0;
	for(int i = 0;i<N;i++)
	{
		for(int j = 0;j<N;j++)
		{
			if(i!=j)
			{
				fract d = Dist(puntos[i],puntos[j]);
				fract tasa = d/lados[0];
				fract d1 = tasa*lados[1];
				fract d2 = tasa*lados[2];
				int t1 = dist[i][d1].size();
				int t2 = dist[j][d2].size();
				if(t1<t2)
				{
					for(auto k : dist[i][d1])
						if(dist[j][d2].count(k))
							res++;
				}
				else
				{
					for(auto k : dist[j][d2])
						if(dist[i][d1].count(k))
							res++;
				}
			}
		}
	}
	if(numQ == 1) return res/2;
	if(numQ == 3) return res/6;
	return res;
}
int main(int argc, char **argv)
{
	int N;
	while(cin>>N)cout<<Caso(N)<<endl;
	return 0;
}

