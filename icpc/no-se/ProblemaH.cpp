#include <bits/stdc++.h>
using namespace std;
int main(){
	int a,d;
	while(cin>>a>>d){
		if(a==0){
			break;
		}
		vector <int> v;
		vector <int>  v1;
		for(int i=0;i<a;i++){
			int b;
			cin>>b;
			v.push_back(b);
		}
		for(int i=0;i<d;i++){
			int b;
			cin>>b;
			v1.push_back(b);
		}
		sort(v.begin(),v.end());
		sort(v1.begin(),v1.end());
		if(v[0]<v1[1]){
			cout<<"Y"<<endl;
		}
		else{
			cout<<"N"<<endl;
			
		}
	}

	
}
