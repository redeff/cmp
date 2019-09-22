#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	while(cin>>n){
	int k;
	cin>>k;
	int pos=0;
	bool ans=1;
	vector <int> v;
	for(int i=0;i<k;i++){
		int a;
		cin>>a;
		v.push_back(a);
	}
	for(int i=1;i<k-1;i++){
		if((v[i]-v[i-1])>0 && (v[i]-v[i+1])>0){
			pos=i;
			break;
		}
	}
	if(pos==0){
		for(int i=pos;i<k-1;i++){
			if(abs(v[i]-v[i+1])<3 && abs (v[i]-v[i+1])>0){
			}
			else{
				ans=0;
			}
			if(v[i]<3 && v[i+1]<3){
				ans=0;
				
			}
		}
		
	}
	else{
		
	for(int i=pos;i<k-1;i++){
		if(v[i]-v[i+1]<3 && v[i]-v[i+1]>0){
			
		}
		else{
			ans=0;
		}
		if(v[i]<3){
			ans=0;
		}
	}
	for(int i=pos;i>0;i--){
		if(v[i]-v[i-1]<3 && v[i]-v[i-1]>0){
			
		}
		else{
			ans=0;
		}
		if(v[i]<3){
			ans=0;
		}
	}
	if(v[pos-1]==v[pos+1]){
		ans=0;
	}
	
	}
	if(ans){
		cout<<"S"<<endl;
	}
	else{
		cout<<"N"<<endl;
	}
	}
	
}

