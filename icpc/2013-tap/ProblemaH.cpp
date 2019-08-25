#include <bits/stdc++.h>
using namespace std;
int N=1000010;
int main(){
	
	vector <int> dp(N,0);
	for(int i=2;i<N;i++){
		if(dp[i]==0){
			for(int j=i;j<=N;j+=i){
				dp[j]+=i;	
			}
		}
	}
	vector <int> dp1(N,0);
	dp1[1]=0;
	int maxi=0;
	for(int i=2;i<N;i++){
		if(dp[i]==i){
			dp1[i]=1;
		}
		else{
			dp1[i]=dp1[dp[i]]+1;
		}
		maxi=max(dp1[i],maxi);
	}
	vector <vector <int > > v(N,vector <int>(20));
	for(int i=2;i<N;i++){
		for(int j=0;j<20;j++){
			v[i][j]=v[i-1][j];
		}
		v[i][dp1[i]]++;
	}
	int t;
	cin>>t;
	while(t>0){
		int a,b,c;
		cin>>a>>b>>c;
		if(c>=20){
			cout<<0<<endl;
		}
		else{
			cout<<v[b][c]-v[a-1][c]<<endl;
		}
		
		
		
		t--;
	}
}
