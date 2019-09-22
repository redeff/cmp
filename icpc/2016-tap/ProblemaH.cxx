/*
 * ProblemaH.cxx
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
using namespace std;
double Caso(int N, int X, int Y)
{
	vector<vector<double> > DP(N+1,vector<double>(N+1,0));
	DP[X-1][N-X] = 1;
	double res = 0;
	for(int i = X-1;i>=0;i--)
	{
		for(int j = N-X;j>=0;j--)
		{
			if(j+i+1<Y) continue;
			//cout<<i<<" __ "<<j<<endl;
			if(j+i+1==Y)
			{
		//		cout<<"EL CASO ES "<<i<<" , "<<j<<" con prob "<<DP[i][j]<<endl;
				if(i==0 && j==0)
				{
					res+=DP[0][0];
					continue;
				}
				double tot = i+j+1;
				double CF = tot*(tot-1)/2;
				double cantf = i/CF;
				res += cantf*DP[i][j];
			}
			else
			{
				double tot = i+j+1;
				double CF = tot*(tot-1)/2;
				double elimW = j*(i+1)/CF + (j*(j-1)/2)/CF;
				double elimB = (i*(i-1)/2)/CF;
				if(i>0)DP[i-1][j] += DP[i][j] * elimB;
				if(j>0)DP[i][j-1] += DP[i][j] * elimW;
			}
		}
	}
	//for(auto k : DP)
	//{
	//	cout<<endl;
	//	for(auto j : k)
	//		cout<<j<<" ";
	//}
	return res;
}
int main(int argc, char **argv)
{
	int N,X,Y;
	while(cin>>N>>X>>Y) printf("%.4f\n",Caso(N,X,Y));
	return 0;
}

