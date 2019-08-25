#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	vector <int> v;
	vector <int> v1;
	for(int i=0;i<n;i++){
		int a;
		cin>>a;
		v.push_back(a);
	}
	for(int i=0;i<n;i++){
		int a;
		cin>>a;
		v1.push_back(a);
	}
	int index=0;
	sort(v.begin(),v.end());
	sort(v1.begin(),v1.end());
	int ans=0;
	for(int i=0;i<n;i++){
		if(v1[i]>v[index]){
			index++;
			ans++;
		}
	}
	cout<<ans<<endl;
}
