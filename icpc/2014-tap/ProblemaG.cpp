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
	sort(v.begin(),v.end());
	vector <int> v1;
	int sum=0;
	for(int i=0;i<n/2;i++){
		v1.push_back(v[i*2+1]-v[i*2]);
		sum+=(v[i*2+1]-v[i*2]);
	}
	if(sum==0){
		cout<<-1<<endl;
		return 0;
	}
	int ans=0;
	
	sort(v1.begin(),v1.end());
	for(int i=0;i<n/2;i++){
		if(sum>v1[i]*2){
			ans++;
			sum-=(v1[i]*2);
			
		}
	}
	cout<<ans<<endl;

}
