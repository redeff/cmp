#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	while(cin>>n&&n!=-1){
		int tot=0;
		int count=0;
		for(int i=0;i<n;i++){
			int a;
			cin>>a;
			tot+=a;
			if(tot%100==0){
				count++;
				tot=0;
			}
		}
		cout<<count<<endl;
	}
}
