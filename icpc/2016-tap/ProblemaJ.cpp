#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,l,c;
	while(cin>>n>>l>>c){
		vector <int> v;
		for(int i=0;i<n;i++){
			int a;
			cin>>a;
			v.push_back(a);
		}
		sort(v.begin(),v.end());
		reverse(v.begin(),v.end());
		int cant;
		if(n%l==0){
			cant=n/l;
		}
		else{
			cant=n/l+1;
		}
		int sum=0;
		for(int i=0;i<cant;i++){
			sum+=v[i*l];
		}
		if(sum>c){
			cout<<"N"<<endl;
		}
		else{
			cout<<"S"<<endl;
		}
		
	}
}
