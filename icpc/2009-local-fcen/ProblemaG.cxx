#include <bits/stdc++.h>
using namespace std;

int main(){
	int a,b;
	
	while(cin>>a&&cin>>b){
		if(a==-1){
			break;
		}
		if(a==1||b==1){
			cout<<a*b*13+52+38*(max(a,b)*2-2)<<endl;
		}
		else if(a*b%2==0){
			cout<<a*b*13+52+38*(a*b)<<endl;
		}
		else{
			cout<<a*b*13+52+38*(a*b+1)<<endl;
		}
	}
}
