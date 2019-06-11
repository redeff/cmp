#include <bits/stdc++.h>
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

typedef long long intl;
vector <vector <intl> > v(2300,vector <intl> (2300,(intl) 1000000000000000));

void llenar(){
	for(intl i=1;i<2300;i++){
		for(intl j=0;j<=i;j++){
			if(j==0||j==i){
				v[j][i-j]=1;
			}
			else{
				if(v[j-1][i-j]>10000000000&&v[j][i-j-1]>10000000000){
					
				}
				else{
					v[j][i-j]=v[j-1][i-j]+v[j][i-j-1];
				}
				
			}
		}
	}
}
int main(){
	v[0][0]=1;
	intl k;
	llenar();
	while(cin>>k&&k!=-1){
		intl ans=0;
		for(intl i=3;i<2300;i++){
			vector<intl>::iterator up;
			up=upper_bound(v[i].begin(),v[i].end(),k);
		
			ans+=(max(intl(up-v[i].begin())-3,intl(0)));
		}
		ans+=1;
		ans+=2*(k-2);
		if(k>=6){
			ans++;
		}
		for(intl i=4;i<=100000;i++){
			if(i*(i+1)/2<=k){
				ans+=2;
			}
			else{
				break;
			}
		}
		cout<<ans<<endl;
		
	}
}
