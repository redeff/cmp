/*
 * ProblemaC.cxx
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
using namespace std;
void DFS(int n, vector<bool> & visit, vector<vector<int> > & Ary, int & Tam, int & CantH)
{
	if(visit[n])
		return;
	visit[n] = true;
	if(Ary[n].size() == 1)
		CantH++;
	Tam ++;
	for(auto k : Ary[n])
		DFS(k,visit,Ary,Tam,CantH);
}
bool Caso()
{
	int N,M;
	cin>>N>>M;
	if(N == -1)
		return false;
	vector<vector<int> > Ary(N);
	vector<bool> visit(N,false);
	int C0 = 0, C1 = 0, Tot = 0;
	for(int i = 0;i<M;i++)
	{
		int a,b;
		cin>>a>>b;
		a--,b--;
		Ary[a].push_back(b);
		Ary[b].push_back(a);
	}
	int HT = 0;
	for(int i = 0;i<N;i++)
	{
		if(visit[i] == 0)
		{
			int tam = 0, canth = 0;
			DFS(i,visit,Ary,tam,canth);
			if(tam == 1)
				C0++;
			else if(tam == 2)
				C1++;
			else
			{
				if(canth==1)
					Tot ++;
				else
					HT += canth;
			}
		}
	}
	Tot += (HT+1)/2;
	if(Tot == 0 && (C0+C1) && (C1 == 0 || C0 == 0) && C1 < 2 && (C0 + C1*2)<N)
		Tot ++;
	Tot += C0 + C1;
	cout<<Tot<<endl;
	return true;
}
int main(int argc, char **argv)
{
	while(Caso());
	return 0;
}

