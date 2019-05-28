/*
 * ProblemaC2.cxx
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
#include <cstdio>
#include <cstring>
#include <queue>
#define ll long long
using namespace std;
int in[200000];
ll dp[200000];
ll abss(ll x)
{
	if(x < 0)
		return -x;
	return x;
}
ll Recursive(int ini, int fin)
{
	if(ini == fin-1)
	{
		return dp[fin]-dp[ini-1];
	}
	if(ini >= fin)
		return 0;
	ll vini = dp[ini];
	ll tot = dp[fin]-dp[ini-1];
	int a = ini, b = fin;
	while(b-a > 1)
	{
		int m = (a+b)/2;
		ll v = dp[m]-dp[ini-1];
		if(v*2 > tot)
			b = m;
		else
			a = m;
	}
	ll Va = dp[a] - dp[ini-1];
	ll Vb = dp[b] - dp[ini-1];
	ll difa = abss(tot-Va*2), difb = abss(tot-Vb*2);
	if(difb < difa)
		a++;
	return tot + Recursive(ini,a) + Recursive(b,fin);
	//ll R2 = tot + Recursive(ini,a+1) + Recursive(b+1,fin);
	//return min(R1,R2);
}
ll Caso()
{
	int N;
	cin>>N;
	dp[0] = 0;
	/*
	for(int i = 1;i<=N;i++)
	{
		scanf("%d",in+i);
		dp[i] = dp[i-1] + in[i];
	}
	return Recursive(1,N);
	*/
	priority_queue<ll,vector<ll>,greater<ll> > PQ;
	for(int i = 0;i<N;i++)
	{
		int k;
		scanf("%d",&k);
		PQ.push(k);
	}
	ll sum = 0;
	while(PQ.size()>1)
	{
		ll a = PQ.top();
		PQ.pop();
		ll b = PQ.top();
		PQ.pop();
		ll s = a+b;
		PQ.push(s);
		sum += s;
	}
	return sum;
}
int main(int argc, char **argv)
{
	int T;
	cin>>T;
	while(T--)
	{
		cout<<Caso();
		if(T>=1)
			cout<<endl;
	}
	return 0;
}

