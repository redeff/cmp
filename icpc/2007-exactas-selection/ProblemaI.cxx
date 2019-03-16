/*
 * ProblemaI.cxx
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
#include <algorithm>
using namespace std;

double abss(double x)
{
	if(x<0)
		return -x;
	return x;
}
bool Case()
{
	double N,M;
	cin>>M>>N;
	if(N == -1)
		return false;
	double F = (M/N);
	double minD = 1e12, Kr = -1;
	double e = 0.00000;
	for(double k = 0;k<=20;k++)
	{
		double f = k/20.0;
		double d = abss(F-f);
		if(d <= minD + e)
			minD = d,Kr = k;
	}	
	double minD2 = 1e12, Pr = -1;
	for(double p = 0;p<=100;p++)
	{
		double f = p/100.0;
		double d = abss(F-f);
		if(d <= minD2 + e)
			minD2 = d,Pr = p;
	}		
	int Ki = Kr;
	string r = string(Ki,'*')+string(20-Ki,'-');
	string n ="";
	int Pi = Pr;
	if(Pi == 0)
		n = "0";
	else
	{
		while(Pi)
			n+=('0'+Pi%10),Pi/=10;
	}
	reverse(n.begin(),n.end());
	n+='%';
	if(n.size()==2)
		r[9] = n[0], r[10] = n[1];
	else if(n.size()==3)
		r[9] = n[0], r[10] = n[1],r[11]=n[2];
	else
		r[8] = n[0], r[9] = n[1], r[10] = n[2], r[11] = n[3];
	cout<<r<<endl;
	//cout<<r.substr(0,10-(Pr==100))<<int(Pr)<<"%"<<r.substr(10)<<string(Pr<10,'-')<<endl;
	return true;
}
int main(int argc, char **argv)
{
	while(Case());
	
	return 0;
}

