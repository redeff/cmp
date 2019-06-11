#include <bits/stdc++.h>
using namespace std;
vector <int> primes={2,3,5,7,11,13,17,19};
int mayorpot(int n,int k){
	int aux=k;
	while(n%aux==0){
		aux*=k;
	}
	return (aux/k);
}
int main(){
	string s;
	while(cin>>s&&s!="*"){
		
		int n = s.size();
		int m1 = primes.size();
		map<int,int> m;
		for(int i=1;i<=n;i++){
			if(s[i-1]=='Y'){
				for(int j=0;j<m1;j++){
					int k=primes[j];
					
					if(i%k==0){
						int r=mayorpot(i,k);
						if(m.count(k)){
							m[k]=max(m[k],r);
						}
						else{
							m[k]=r;
						}
					}
				}
			}
		}
		int ans=1;
		for(auto x:m){
			ans*=x.second;
		}
		
		for(int i=1;i<=n;i++){
			if(s[i-1]=='Y'){
				if(ans%i!=0){
					ans=-1;
					break;
				}
			}
			else{
				if(ans%i==0){
					ans=-1;
					break;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0 ;
}
