/*
 * ProblemaJ.cxx
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
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
double Pg[8][8], Pm[8][8], Ge[8][8];
void ProjectSet(int J, int D,double posi, double posj, double & pi, double & pj, double & pg)
{
	vector<vector<double> > Pos(2001,vector<double>(2001,0));
	Pos[0][0] = 1;
	for(int i = 0;i<2000;i++)
		for(int j = 0;j<2000;j++)
		{
			if(i > J && i-j==D)
				pi += Pos[i][j];
			else if(j > J && j-i==D)
				pj += Pos[i][j];
			else
			{
				pg += Pos[i][j];
				Pos[i+1][j] += Pos[i][j] * posi;
				Pos[i][j+1] += Pos[i][j] * posj;
			}
		}
	
}
vector<double> Instanse(int in[], int N, int ini, int fin, double & Project)
{
	int mid = (ini+fin)/2;
	if(ini == fin)
	{
		vector<double> ret(N,0);
		ret[in[ini]] = 1;
		return ret;
	}
	vector<double> A = Instanse(in,N,ini,mid,Project);
	vector<double> B = Instanse(in,N,mid+1,fin,Project);
	vector<double> Ret(N,0);
	for(int i = 0;i<N;i++)
	{
		for(int j = 0;j<N;j++)
		{
			if(i!=j)
			{
				double pi = A[i], pj = B[j]; 
				double pgame = pi*pj;
				Ret[i] += pgame * Pg[i][j];
				Ret[j] += pgame * Pg[j][i];
				Project += pgame * Ge[i][j];
			}
		}
	}
	return Ret;
}
bool Caso()
{
	int K,S,J,D;
	cin>>K>>S>>J>>D;
	if(K == -1)
		return false;
	cout<<"CASO"<<endl;
	int N = 1<<K;
	for(int i = 0;i<N;i++)
		for(int j = 0;j<N;j++)
		{
			int a;
			scanf("%d",&a);
			Pg[i][j] = double(a)/double(100);
		}
	for(int i = 1;i<N;i++)
	{
		for(int j = 0;j<i;j++)
		{
			Ge[i][j] = 0;
			double posi = 0, posj = 0, prog = 0, pros = 0,ganai = 0, ganaj = 0;
			ProjectSet(J,D,Pg[i][j],Pg[j][i],posi,posj,prog);
			cout<<prog<<endl;
			ProjectSet(S,0,posi,posj,Pm[i][j],Pm[j][i],pros);
			Ge[i][j] = Ge[j][i] = (pros*prog);
			cout<<i<<" vs "<<j<<" : "<<prog<<" * "<<pros<<" = "<<Ge[i][j]<<endl;
		}
	}
	int in[N];
	for(int i = 0;i<N;i++)
			in[i] = i;
	double MaxG = 0;
	do{
		double Games = 0;
		Instanse(in,N,0,N-1,Games);
		if(Games > MaxG)
			MaxG = Games;
	}while(next_permutation(in,in+N));
	printf("%.2f\n",MaxG);
	return true;
}
int main(int argc, char **argv)
{
	while(Caso());
	return 0;
}

