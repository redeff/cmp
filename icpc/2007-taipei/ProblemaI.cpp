#include <bits/stdc++.h>
using namespace std;
int dfsdp(int v,int father,vector <int> &weights,vector <vector <int> > &adj,vector <int> &dp){
	bool f=1;
	int sum=weights[v];
	for(auto x: adj[v]){
		if(x!=father){
			f=0;
			sum+=dfsdp(x,v,weights,adj,dp);
		}
	}
	if(f){
		dp[v]=weights[v];
		return dp[v];
	}
	dp[v]=sum;
	return dp[v];
}
int ans=0;
void dfs(int v,int father,vector <int> &weights,vector <vector <int> > &adj,vector <int> &dp,vector <int> &rta){
	int sumi=0,index=-1;
	for(auto x:adj[v]){
		if(x!=father){
			if(sumi<dp[x]){
				sumi=dp[x];
				index=x;
			}
			else if(sumi==dp[x]){
				if(x>index){
					index=x;
				}
			}
		}
	}
	if(index==-1){
		ans+=weights[v];
		return;
	}

	ans+=weights[v];
	rta.push_back(index);
	dfs(index,v,weights,adj,dp,rta);
}
int main(){
	int t;
	cin>>t;
	while(t>0){
		int n,root;
		ans=0;
		cin>>n>>root;
		vector <vector <int> > adj(n);
		vector <int> weights (n,0);
		for(int i=0;i<n;i++){
			int w,m;
			cin>>w>>m;
			weights[i]=w;
			for(int j=0;j<m;j++){
				int a;
				cin>>a;
				adj[i].push_back(a);
			}
		}
		vector <int> dp(n,0);
		dfsdp(root,-1,weights,adj,dp);
		vector <int> rta={root};
		dfs(root,-1,weights,adj,dp,rta);
		cout<<ans<<endl;
		int k=rta.size();
		for(int i=0;i<min(k,10);i++){
			if(i==min(k,10)-1){
				cout<<rta[i];
			}
			else{
				cout<<rta[i]<<" ";
			}
			
		}
		cout<<endl;
		for(int i=10;i<k;i++){
			
			if(i==k-1){
				cout<<rta[i];
				cout<<endl;
			}
			else{
				cout<<rta[i]<<" ";
			}
		}
		
		t--;
	}
}
