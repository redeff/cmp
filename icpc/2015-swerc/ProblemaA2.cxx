/*
 * ProblemaA2.cxx
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
#include <bitset>
using namespace std;
int A,B,E,P;
vector<vector<int> > Ary;
bitset<5001> G[5001], used;
int orden[5001];
void DFS(int n, int &r)
{
	if(used[n])
		return;
	used[n] = true;
	for(auto k : Ary[n])
		DFS(k,r);
	orden[r] = n;
	r--;
} 
bool Probar(int N, int n)
{
	int t = 0;
	for(int i = 0;i<E;i++)
		if(G[i][n] == false)
			t++;
	//cout<<N<<" y "<<n<<" = "<<t<<endl;
	return (t<N);
}
int main(int argc, char **argv)
{
	cin>>A>>B>>E>>P;
	Ary.resize(E+1);
	for(int i = 0;i<P;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		Ary[a].push_back(b);
	}
	int r = E-1;
	for(int i = 0;i<E;i++)
	{
		DFS(i,r);
	}
	for(int i = 0;i<E;i++)
	{
		int j = orden[i];
		G[j][j] = true;
		for(auto k : Ary[j])
			G[k] |= G[j];
	}
	int rA = 0, rB = 0, rC = 0;
	for(int i = 0;i<E;i++)
	{
		rA += Probar(A,i), rB += Probar(B,i);
	//	cout<<i<<" = ";
	//	for(int l = 0;l<E;l++)
	//		cout<<G[i][l];
	//	cout<<endl;
		if(G[i].count() > B)
			rC++;
	}
	cout<<rA<<endl<<rB<<endl<<rC<<endl;
	return 0;
}
