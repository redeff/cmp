#include <bits/stdc++.h>
using namespace std;
typedef long long intl;
int main(){
	intl n;
	cin>>n;
	vector <intl> v;
	intl ans=0;
	for(intl i=0;i<n;i++){
		intl a;
		cin>>a;
		v.push_back(a);
		ans+=a;
		ans+=((a)*(n-1)*3);
	}
	
	vector <intl> v1(21,0);
	for(intl i=0;i<=20;i++){
		for(intl j=0;j<n;j++){
			intl r=(v[j]&(1<<i));
			if(r){
				v1[i]++;
			}
			
		}
	}
	for(intl i=0;i<=20;i++){
		for(intl j=0;j<n-2;j++){
			if(v[j]&(1<<i)){
				v1[i]--;
			}
			
			intl l=v1[i];
			intl r=n-j-v1[i]-1;
			if(v[j]&(1<<i)){
				ans+=r*(r-1)*(1<<i)*3;
				ans+=l*(l-1)*(1<<i)*3;
			}
			else{
				ans+=l*(r)*(1<<i)*6;
			}
			
			
		}
	}
	cout<<ans<<endl;
	
}
