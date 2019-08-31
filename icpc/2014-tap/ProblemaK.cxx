/*
 * ProblemaK.cxx
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
#include <cstdio>
using namespace std;
struct seg{
	int ini, fin, aum = 0;
	bool r;
	int size()
	{
		return fin-ini+1;
	}
	int index(int i)
	{
		if(r)
			return fin-i;
		else
			return ini+i;
	}
	
};
void Revertir(vector<seg> & r)
{
	reverse(r.begin(),r.end());
	for(auto & k : r)
		k.r = !k.r, k.aum ++;
}
vector<seg> Concatenar(vector<vector<seg> > in)
{
	vector<seg> res;
	for(auto & k : in)
		for(auto & j : k)
			res.push_back(j);
	return res;
}
seg Gen(int _i, int _j, bool _r)
{
	seg r;
	if(_i > _j) swap(_i,_j);
	r.ini = _i;
	r.fin = _j;
	r.r = _r;
	return r;
}

string Regenerar(string prev, vector<seg> segs)
{
	int L = prev.size();
	string res(L,'0');
	int ini = 0;
	for(auto k : segs)
	{
		int c = k.fin - k.ini+1;
		for(int i = 0;i<c;i++)
		{
			int p;
			if(k.r)
				p = k.fin - i;
			else
				p = k.ini + i;
			res[ini] = prev[p];
			ini++;	
		}
	}
	return res;
}
pair<seg,bool> Inter(seg s, int ini, int fin, int c)
{
	int sini = c+1;
	int sfin = c+s.size();
	int a = max(sini,ini);
	int b = min(sfin,fin);
	seg r;
	if(a > b)
		return {r,false};
	int rini = a - sini;
	int rfin = b - sini;
	r.ini = s.index(rini);
	r.fin = s.index(rfin);
	r.r = s.r;
	r.aum = s.aum;
	if(r.ini > r.fin)
		swap(r.ini,r.fin);
	return {r,true};
}
void ProcesarSeg(seg s,int c, int i, int j, int k, int l, vector<seg> & p1,  vector<seg> & p2,  vector<seg> & p3,  vector<seg> & p4,  vector<seg> & p5, int L)
{
	/// [0,i)
	///	[i,j]
	///	(j,k) 
	/// [k,l] 
	/// (l,L-1]
	
	auto a = Inter(s,0,i-1,c);
	auto b = Inter(s,i,j,c);
	auto cs = Inter(s,j+1,k-1,c);
	auto d = Inter(s,k,l,c);
	auto e = Inter(s,l+1,L-1,c);
	if(a.second)
		p1.push_back(a.first);
	if(b.second)
		p2.push_back(b.first);
	if(cs.second)
		p3.push_back(cs.first);
	if(d.second)
		p4.push_back(d.first);
	if(e.second)
		p5.push_back(e.first);
		
}  
vector<seg> Partir(int i, int j, int k, int l, vector<seg> segs, int L)
{
	vector<seg> p1,p2,p3,p4,p5;
	int c = 0;
	for(auto ks : segs)
	{
		ProcesarSeg(ks,c,i,j,k,l,p1,p2,p3,p4,p5,L);
		c += ks.size();
	}
	Revertir(p2);
	Revertir(p4);
	return Concatenar({p1,p2,p3,p4,p5});
}
void Caso()
{
	string S;
	int N;
	cin>>S>>N;
	int L = S.size(); 
	vector<seg> segs = {Gen(0,L-1,false)};
	for(int n = 0;n<N;n++)
	{
		int i,j,k,l;
		scanf("%d %d %d %d",&i,&j,&k,&l);
		segs = Partir(i-1,j-1,k-1,l-1,segs,L);
		for(auto ks : segs)
		{
			cout<<ks.ini<<" a "<<ks.fin<<endl;
		}
		cout<<"---------"<<endl;
		if(segs.size() * segs.size() > 2 * L)
		{
			S = Regenerar(S,segs);
			segs = {Gen(0,L-1,false)};
		}
	}
	cout<<Regenerar(S,segs)<<endl;
}
int main(int argc, char **argv)
{
	int T;
	cin>>T;
	while(T--)Caso();
	return 0;
}

