#include <bits/stdc++.h>
using namespace std;
int main(){
	#ifdef ACMTUYO
		freopen("ProblemaI.in","r",stdin);
	#endif
	int t,p;
	
	while(cin>>t>>p){
		if(t==0){
			break;
		}
		vector <vector<pair<int,int>> > v(11);
		for(int i=0;i<t;i++){
			int time=0,error=0;
			int cant=0;
			for(int j=0;j<p;j++){
				int a;
				char b;
				string c;
				cin>>a>>b>>c;
				if(c=="-"){
					
				}
				else{
					cant++;
					int r=stoi(c);
					time+=r;
					error+=(a-1);
				}
			}
			v[cant].push_back({time,error});	
		}
		int maxi=10000000,mini=1;
		int k=v.size();
		for(int l=0;l<k;l++){
			int k1=v[l].size();
			for(int i=0;i<k1;i++){
				for(int j=0;j<k1;j++){
					int time=v[l][i].first,error=v[l][i].second,time1=v[l][j].first,error1=v[l][j].second;
					if(time+error*20==time1+error1*20){
						if((time1-time)!=0){
							mini=20;
							maxi=20;
						}
					}
					if(time+error*20>time1+error1*20){
						
						if(error-error1>0){
							
							mini=max(mini,(time1-time)/(error-error1)+1);
						}
						else if((error-error1)==0){
					
						}
						else{
							int aux=1;
							if((time1-time)%(error-error1)!=0){
								aux=0;
							}
							maxi=min(maxi,(time1-time)/(error-error1)-aux);
						}
					}
				
				}
			}
		}
		if(maxi==10000000){
			cout<<mini<<" *"<<endl;
		}
		else{
			cout<<mini<<" "<<maxi<<endl;
		}
	}
}
/*
 5 3
 0/- 0/- 0/-
 2/- 2/- 1/- 
 1/60 1/165 1/-
 1/80 0/- 2/120
 0/- 1/17 0/-
 4 2
 17/- 5/-
 2/7 3/-
 3/- 2/-
 1/15 0/-
 3 2
 1/- 2/15
 2/53 1/17
 1/70 1/20
 0 0
*/

