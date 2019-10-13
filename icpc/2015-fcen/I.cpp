#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	
	while(cin>>n){
		int ans=0;
		for(int i=0;i<5;i++){
			int a;
			cin>>a;
			if(a==n){
				ans++;
			}
		}
		cout<<ans<<endl;
	}
}
