#include <bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		
		int n;
		cin>>n;
		vector <int> v;
		for(int i=0;i<n;i++){
			int a;
			cin>>a;
			v.push_back(a);
		}
		sort(v.begin(),v.end());
		int r=v[0]/(n+1);
		for(int i=0;i<n;i++){
			v[i]-=(r*(n+1));
		}
		bool flag=0;
		for(int i=0;i<n;i++){
			if(v[i]<i+1){
				flag=1;
			}
		}
		if(flag){
			cout<<"S"<<endl;
		}
		else{
			cout<<"N"<<endl;
		}
	}
	

}
