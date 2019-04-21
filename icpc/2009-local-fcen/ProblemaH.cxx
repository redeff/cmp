#include <bits/stdc++.h>
using namespace std;
typedef long long intl;
int main(){
	intl n;
	while(cin>>n){
		if(n==-1){
			break;
		}
		map<intl,intl> m;
		intl aux=n;
		for(intl i=2;i<=1e6;i++){
			if(aux%i==0){
				while(aux%i==0){
					if(m.count(i)){
						m[i]++;
					}
					else{
						m[i]=1;
					}
					aux/=i;
				}
			}
		}
		intl ent=1,raiz=1;
		intl k=intl(sqrt(aux));
		if(k*k==aux){
			m[k]=2;
		}
		else{
			m[aux]=1;
		}
		for(auto x: m){
			ent*=pow(x.first,x.second/2);
			if(x.second%2==1){
				raiz*=x.first;
			}
		
		}
		cout<<ent<<" "<<raiz<<endl;
	}
}
