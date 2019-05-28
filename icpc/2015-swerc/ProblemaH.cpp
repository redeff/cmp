#include <iostream>
#include <set>
#include <math.h>
using namespace std;
typedef unsigned long long intl;
set <intl> s;
intl uno = 1;
void make(intl n,intl m){
	intl curr=0;
	intl num=0;
	while(curr<=63){
		if(curr+m>63&&curr!=0){
			break;
		}
		num*=uno<<m;
		s.insert(num);
		num*=(uno<<n);
		if(curr+m+n>63&&curr!=0){
			break;
		}
		num+=((uno<<n)-1);
		s.insert(num);
		if(curr==0){
			curr+=n;
		}
		else{
			curr+=n+m;
		}
		
	}
}
int main(){
	for(int i=1;i<=63;i++){
		for(int j=1;j<=63;j++){
			make(i,j);
		}
	}
	s.erase(0);
	intl k=(uno<<63);  
	s.insert(k);
	intl a,b;
	while(cin>>a &&cin>>b){
		intl ans=0;
		for(auto x:s){
			if(a<=x && x<=b){
				
				ans++;
			}
		}
		cout<<ans<<endl;
	}
	
	
	
	
	
}
