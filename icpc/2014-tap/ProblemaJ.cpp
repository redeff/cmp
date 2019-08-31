#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin>>n;
	vector <int> v;
	for(int i=0;i<n;i++){
		int a;
		cin>>a;
		v.push_back(a);
	}
	vector <int> dp(n+1,0);
	dp[n]=1;
	for(int i=n-1;i>=0;i--){
		if(v[i]+i+1<=n){
			dp[i]=dp[v[i]+i+1];
		}
	}
	for(int i=1;i<n;i++){
		if(dp[i]){
			cout<<i<<endl;
		}
	}
	cout<<n<<endl;
	
	
}
