/*
 * ProblemaC.cxx
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
#include <cstdio>
using namespace std;
typedef long long intl;
bool EsLetra(char c)
{
	return ('A'<=c && c<='Z');
}
int Tipe(string s)
{
	if(EsLetra(s[3])!=EsLetra(s[4])) return -1;
	if(!EsLetra(s[0])||!EsLetra(s[1])||(!EsLetra(s[2])))return -1;
	if(EsLetra(s[5])||EsLetra(s[6])) return -1;
	if(EsLetra(s[3])) return 2;
	return 1;
}
intl pesos2[7],pesos1[7], Mviejo = 0;

intl ValorLetra1(char c)
{
	if(c>='0' && c<='9') return c-'0';
	return c-'A';	
}
intl Ponderar1(string s)
{
	intl res = 0;
	for(int i = 6;i>=0;i--) res+=ValorLetra1(s[i])*pesos1[i];
	return res;
}
intl ValorLetra2(char c)
{
	if(c>='0' && c<='9') return c-'0';
	intl v = c-'A';
	if(c>'A') v--;
	if(c>'C') v--;
	if(c>'I') v--;
	if(c>'M') v--;
	if(c>'P') v--;
	return v;
}
intl Ponderar2(string s)
{
	intl res = Mviejo+1;
	for(int i = 6;i>=0;i--) res += ValorLetra2(s[i]) * pesos2[i];
	return res;
}
bool TieneIlegales(string s)
{
	for(auto k : s) if(k=='A'||k=='C'||k=='I'||k=='M'||k=='P') return true;
	return false;
}
bool Caso()
{
	string Sm, Si;
	intl C;
	cin>>Sm>>Si>>C;
	if(Si == "*") return false;
	int tm = Tipe(Sm);
	int ti = Tipe(Si);
	if(ti == -1) {cout<<"N\n";return true;}
	intl vm = 0;
	if(tm == 1) vm = Ponderar1(Sm);
	else vm = Ponderar2(Sm);
	intl vi = 0;
	if(ti == 1) vi = Ponderar1(Si);
	else{
		if(TieneIlegales(Si)){cout<<"N\n";return true;}
		vi = Ponderar2(Si);
	}
	//cout<<vm<<" vs "<<vi<<endl;
	if(vm>=vi || vi-vm>C) {cout<<"N\n";return true;}
	{cout<<"Y\n";return true;}
}
int main(int argc, char **argv)
{
	pesos2[6] = 1;
	pesos2[5] = 10;
	pesos2[4] = 100;
	intl d = 'Z'-'A'+1;
	for(int i = 3;i>=0;i--) pesos2[i] = pesos2[i+1]*(d-5);
	
	pesos1[6] = 1;
	pesos1[5] = 10;
	pesos1[4] = 100;
	pesos1[3] = 1000;
	pesos1[2] = 10000;
	pesos1[1] = pesos1[2]*d;
	pesos1[0] = pesos1[1]*d;
	
	string Sm, Si;
	Mviejo = Ponderar1("ZZZ9999");
	intl C;
	while(Caso());
	return 0;
}

