#include <bits/stdc++.h>
using namespace std;
typedef long long intl;
int dp1[70][2];
string pasb(int n,int b){
	string vac;
	while(n>0){
		vac.push_back((n%b)+'0');
		n/=b;
	}
	reverse(vac.begin(),vac.end());
	return vac;
}
void dp(int pos,bool flag,string &s,string &s1){
	int n=s1.size();
	if(!flag){
		for(int i=0;i<n;i++){
			dp1[pos+1][0]+=dp1[pos][0];
		}
	}
	else{
		for(int i=0;i<n;i++){
			if(s1[i]==s[pos]){
				dp1[pos+1][1]+=dp1[pos][1];
			}
			if(s1[i]<s[pos]){
				dp1[pos+1][0]+=dp1[pos][1];
			}
		}
	}	
}
int main(){
	int l,r,b;
	string s;
	while(cin>>l>>r>>b>>s&&l!=-1){
		string s1;
		for(int i=0;i<int(s.size());i++){
			if(s[i]=='S'){
				s1.push_back(i+'0');
			}
		}
		
		string lb,rb;
		lb=pasb(l,b);
		rb=pasb(r,b);
		
		dp1[0][1]=1;	
		for(int i=0;i<int(lb.size());i++){
			dp(i,1,lb,s1);
			dp(i,0,lb,s1);
		}
		int ans=dp1[lb.size()][0]+dp1[lb.size()][1];
		for(int i=0;i<70;i++){
			dp1[i][0]=0;
			dp1[i][1]=0;
		}
		dp1[0][1]=1;
		
		for(int i=0;i<int(rb.size());i++){
			dp(i,1,rb,s1);
			dp(i,0,rb,s1);
		}
		
		int ans1=dp1[rb.size()][0]+dp1[rb.size()][1];
		cout<<ans<<" "<<ans1<<endl;
		cout<<ans1-ans<<endl;
		
	}
}
