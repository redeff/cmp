#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;
	vector <int> v(k,0);
	for(int i=0;i<k;i++){
		int a;
		cin>>a;
		v[i]=a;
	}
	
	
	int l=1,h=n+1;
	while(h-l>1){
		priority_queue <int> q;
		bool flag=0;
		for(int i=0;i<k;i++){
			q.push(v[i]);
		}
		int mid=(h+l)/2;
		for(int i=0;i<n;i++){
			int a=q.top();
		
			q.pop();
			if(a>=mid){
				a-=mid;
			}
			else{
				flag=1;
			}
			q.push(a);
		}
		if(flag){
			h=mid;
		}
		else{
			l=mid;
		}
		
	}
	cout<<l<<endl;
	priority_queue <pair<int,int>> q;
	for(int i=0;i<k;i++){
		q.push({v[i],i});
	}
	for(int i=0;i<n;i++){
		int a=q.top().first;
		
		int b=q.top().second;
		q.pop();
			if(a>=l){
				a-=l;
			}
		q.push({a,b});
		cout<<b+1<<endl;
	}
	
}
