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
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
vector<vector<string> > in;
int main(int argc, char **argv)
{
	string a;
	map<string,int> app;
	while(cin>>a)
	{
		//cout<<a<<endl;
		if(a[0] == '<')
		{
			if(a == "<text>")
			{
				in.push_back({});
				if(in.size() > 7)
				{
					int d = in.size() - 8;
					for(auto k : in[d])
						app[k]--;
				}
			}
			else if(a=="<top")//if(a[a.size()-2] <= '9' && a[a.size()-2] >= '0')
			{
				int t;
				cin>>t;
				cin>>a;
				auto it = app.end();
				vector<pair<int,string> > local;
				for(auto k : app)
				{
					local.push_back({k.second,k.first});
				//	cout<<k.first<<" => "<<k.second<<endl;
				}
				sort(local.begin(),local.end());
				vector<pair<int,string> > res;
				int p = local.size() - min(t,(int)local.size());
				for(int i = 0;i<local.size();i++)
					if(local[i].first >= local[p].first && local[i].first >= 1)
						res.push_back({-local[i].first,local[i].second});
				sort(res.begin(),res.end());
				cout<<"<top "<<t<<">"<<endl;
				for(auto k : res)
					cout<<k.second<<" "<<-k.first<<endl;
				cout<<"</top>"<<endl;
			}
		}
		else
		{
			if(a.size()>=4)
			{
				in[in.size()-1].push_back(a);
				app[a]++;
			}
		}
	}
	return 0;
}

