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
#include <algorithm>
using namespace std;

double v[11],mixv[11],a[11],x[11],d[11],Q,S;
double e = 0.0000001;
int N,M;
vector<pair<double,double> > ps;
vector<int> sus;
	
int main(int argc, char **argv)
{
	cin>>N>>M>>S;
	for(int i = 0;i<N;i++)
	{
		cin>>v[i]>>a[i];
		sus.push_back(i);
	}
	for(int i = 0;i<M;i++)
	{
		cin>>x[i]>>d[i];
		ps.push_back({x[i],d[i]});
	}
	sort(ps.begin(),ps.end());
	cin>>Q;
	
	while(ps.size() && sus.size())
	{
		vector<int> proximo;
		//cout<<v[0]<<"  "<<v[1]<<" => "<<mixv[0]<<"  "<<mixv[1]<<endl;
		int n = sus[0], j = 0;
		double xl = v[n] / S;
		while(j < ps.size() && ps[j].first <= xl)
			v[n] -= a[n] * ps[j].second * e, j++; 
		if(a[n] * Q * e < v[n])
			mixv[n] += a[n] * Q * e;
		else
			mixv[n] += v[n], v[n] = 0;
		v[n] -= a[n] * Q * e;
		if(v[n] > 0)
			proximo.push_back(n);
		
		for(int i = 1;i<sus.size();i++)
		{
			n = sus[i];
			xl += v[n] / S;
			//mixv[n] += a[n] * Q;
			while(j < ps.size() && ps[j].first <= xl)
				v[n] -= a[n] * ps[j].second * e, j++; 
			//v[n] -= a[n] * Q * e;
			//if(v[n] <= 0)
			//	sus.erase(sus.begin()+i);
			if(v[n] > 0)
				proximo.push_back(n);// cout<<n<<" == "<<v[n]<<endl;
		}
		
		while(j<ps.size())
			ps.pop_back();
		sus = proximo;
		//cout<<proximo.size()<<"  "<<ps.size()<<endl;
	}	
	for(int i = 0;i<N;i++)
	{
		mixv[i] += v[i];
		cout<<mixv[i]<<endl;
	}
}

