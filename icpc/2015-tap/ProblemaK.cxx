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
#include <set>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
const int largo = 1<<17;
int ST[largo], ini, fin, a[60000];
pair<int,int> R[largo];
set<int> Sets[1000001];
int Query(int i)
{
	if(ini<=R[i].first && R[i].second <= fin) return ST[i];
	if(ini>R[i].second || fin<R[i].first) return -1;
	return max(Query(i*2),Query(i*2+1));
}
void Update(int pos, int v)
{
	pos+=largo/2;
	ST[pos] = v;
	while(pos/=2)ST[pos] = max(ST[pos*2],ST[pos*2+1]);
}
void Caso(int N, int R)
{
	memset(ST,0,sizeof(ST));
	for(int i = 0;i<=1000000;i++)Sets[i] = {0};
	for(int i = 1;i<=N;i++)
	{
	//	cout<<"input = "<<i<<endl;
		int s;
		scanf("%d",&s);
		a[i] = s;
		auto v = Sets[s].end();
		v--;
		ST[largo/2+i] = *v;
		Sets[s].insert(i);
	}
	for(int i = 0;i<=1000000;i++)Sets[i].insert(N+10);
	//cout<<"no rompio 1"<<endl;
	for(int i = largo/2-1;i>=0;i--)ST[i] = max(ST[i*2],ST[i*2+1]);
	for(int i = 0;i<R;i++)
	{
		char t;
		cin>>t;
		if(t == 'E')
		{
			int k;
			scanf("%d",&k);
			ini = 1;
			fin = k;
			printf("%d\n",(k-Query(1)));
		}
		else
		{
			int k,s;
			scanf("%d %d",&k,&s);
			int t = a[k];
			a[k] = s;
			auto act = Sets[t].upper_bound(k);
			Sets[t].erase(k);
			int pact = *act;
			act--;
			Update(pact,*act);// cout<<"Updateo : "<<pact<<" a "<<(*act)<<endl;
			auto act2 = Sets[s].upper_bound(k);
			int pact2 = *act2;
			Update(pact2,k);// cout<<"Updateo : "<<pact2<<" a "<<k<<endl;
			Sets[s].insert(k);
			act2--,act2--;
			Update(k,*act2);//  cout<<"Updateo : "<<k<<" a "<<(*act)<<endl;
			
			//for(int i = 1;i<=N;i++)cout<<a[i]<<" ";
			//cout<<endl;
			//for(int i = 1;i<=N;i++)cout<<ST[i+largo/2]<<" ";
			//cout<<endl;
		}
	}
}
int main(int argc, char **argv)
{
	for(int i = 0;i<largo/2;i++) R[i+largo/2] = {i,i};
	for(int i = largo/2-1;i>=0;i--) R[i] = {R[i*2].first,R[i*2+1].second};
	int N,R;
	while(cin>>N>>R)Caso(N,R);
	return 0;
}
/*
4 2
1 2 1 3
E 4   3
E 2   2
10 10
1 2 3 4 5 6 7 8 9 10
E 1   1 
E 2   2
E 3   3
E 4   4
E 5   5
E 6   6
E 7   7  
E 8   8
E 9   9
E 10  10
5 7
1 2 3 4 5
E 3   3
E 5   5
C 3 1 
E 4   3
C 2 5
E 3   2
E 5   3

3
2
1
2
3
4
5
6
7
8
9
10
3
5
3
2
3


*/


