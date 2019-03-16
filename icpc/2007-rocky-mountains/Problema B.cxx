/*
 * Problema B.cxx
 * 
 * Copyright 2019 Unknown <reedef@reedef-pc>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either v
 * ersion 2 of the License, or
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


#include <bits/stdc++.h>
using namespace std;
struct player{
	string name;
	int hit;
	int sacrifice;
};
int safe;
int randi=1;
void simular(int index,vector <player> &v,int out,vector <int> &base,vector <string> &hits,vector<string> &runs){
	if((out==0&&base[2]!=-1)||(out==1&&base[3]!=-1)){
		if(randi*1000<=v[index].sacrifice*65536){
			if(base[3]>=0){
				runs.push_back(v[base[3]].name);
			}
			base[0]=-1;
			for(int i=3;i>=1;i++){
				base[i]=base[i-1];
			}
		}
		out++;
		
			
	}	
	else{
		if(randi*1000<=v[index].hit*65536){
			hits.push_back(v[index].name);
			if(base[3]>=0){
				runs.push_back(v[base[3]].name);
			}
			base[0]=index;
			for(int i=3;i>=1;i++){
				base[i]=base[i-1];
			}
		}
		else{
			out++;
		}
	}	
	randi=(randi*25173+13849)%65536;	
	if(out>=3){
		safe=((index+1)%9);
		return;
	}	
	simular((index+1)%9,v,out,base,hits,runs);
}
int main(){
	int t;
	cin>>t;
	while(t>0){
		string a,b;
		cin>>a;
		vector <player> first;
		vector <player> second;
		for(int i=0;i<9;i++){
			string c;
			double n,m;
			cin>>c>>n>>m;
			player k;
			k.name=c;
			k.hit=n*1000;
			k.sacrifice=m*1000;
			first.push_back(k);	
		}
		cin>>b;	
		for(int i=0;i<9;i++){
			string c;
			double n,m;
			cin>>c>>n>>m;
			player k;
			k.name=c;
			k.hit=n*1000;
			k.sacrifice=m*1000;
			second.push_back(k);	
		}
		randi=1;
		int index1=0,index2=0,score1=0,score2=0,x=0,y=0,aaa=0;
		while(aaa<9||(score1==score2&&aaa>=9)){
			vector <string> v1;
			vector <string> v2;
			vector <string> v3;
			vector <string> v4;
			vector <int> base(4,-1);
			simular(index1,first,0,base,v1,v2);
			index1=safe;
			score1+=v1.size();
			x+=v2.size();
			vector <int> base1(4,-1);
			simular(index2,second,0,base1,v3,v4);
			score2+=v3.size();
			y+=v4.size();
			index2=safe;
			aaa++;
			cout<<aaa<<endl;
			for(int i=0;i<v1.size();i++){
				cout<<v1[i]<<endl;
			}
			for(int i=0;i<v3.size();i++){
				cout<<v3[i]<<endl;
			}
		}
		
		
		t--;
	}
		  
}

