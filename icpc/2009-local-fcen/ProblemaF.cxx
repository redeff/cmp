#include <bits/stdc++.h>
using namespace std;
typedef long long intl;
vector <int> pf(string s){
	int n=s.size();
	vector <int> v(n,0);
	for(int i=1;i<n;i++){
		int check=v[i-1];
		while(1){
			if(s[check]==s[i]){
				v[i]=check+1;
				break;
			}
			if(check==0){
				v[i]=0;
				break;
			}
			else{
				check=v[check-1];
			}
			
		}
	}
	return v;
}
int main(){
	string a;
	while(cin>>a){
		if(a=="*"){
			break;
		}
		int n=a.size();
		vector <int> v=pf(a);
		
		int m=v[n-1];
		if(n%(n-m)==0){
			cout<<n/(n-m)<<endl;
		}
		else{
			cout<<1<<endl;
		}
	}
}
