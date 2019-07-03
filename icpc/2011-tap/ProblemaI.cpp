#include <bits/stdc++.h>
using namespace std;
int r=-1;
int b=-1;
void dfs(vector<vector <int> > &v1,int v,int p,int dist){
	for(auto x:v1[v]){
		if(p!=x){
			if(dist+1>b){
				r=x;
				b=dist+1;
			}
			dfs(v1,x,v,dist+1);
		}
	}
}
int main(){
	int n;
	while(cin>>n&&n!=-1){
		r=-1;
		b=-1;
		vector <vector <int> > v(n);
		for(int i=1;i<n;i++){
			int a;
			cin>>a;
			a--;
			v[i].push_back(a);
			v[a].push_back(i);
		}
		dfs(v,0,-1,0);
		int k=r;
		r=-1;
		b=-1;
		dfs(v,k,-1,1);
		cout<<b/2<<endl;
	}
}
