#include <bits/stdc++.h>
using namespace std;
int dp[1010][1010];
int main(){
	int n,k;
	cin>>n>>k;
	string s;
	cin>>s;
	if(s=="?"){
		cout<<0<<endl;
		return 0;
	}
	if(s[0]=='0'&&s.size()>1){
		cout<<-1<<endl;
		return 0;
	}
	vector <int> modk(1010,1);
	modk[0]=1%k;
	for(int i=1;i<1010;i++){
		modk[i]=(modk[i-1]*10)%k;
	}
	dp[0][0]=1;
	reverse(s.begin(),s.end());
	for(int i=1;i<=n-1;i++){
		if(s[i-1]!='?'){
			int r=s[i-1]-'0';
			for(int j=0;j<1005;j++){
				if(dp[i-1][j]){
					dp[i][(j+r*modk[i-1])%k]=1;
				}
			}
		}
		else{
			for(int j=0;j<1005;j++){
				if(dp[i-1][j]){
					for(int l=0;l<10;l++){
						dp[i][(j+l*modk[i-1])%k]=1;
					}
				}
			}
		}
	}
	
	int sum=0;
	for(int i=n;i>=1;i--){
		int c=0;
		if(n==i){
			c=1;
		}
		if(s[i-1]!='?'){
			int r=s[i-1]-'0';
			if(!dp[i-1][(k-(sum+r*modk[i-1])%k)%k]){
				cout<<-1<<endl;
				return 0;
			}
			sum+=r*modk[i-1];
			sum=sum%k;
		}
		else{
			for(int l=c;l<10;l++){
				if(dp[i-1][(k-(sum+l*modk[i-1])%k)%k]){
					s[i-1]=l+'0';
					sum+=l*modk[i-1];
					sum=sum%k;
					break;
				}
			}
			if(s[i-1]=='?'){
				cout<<-1<<endl;
				return 0;
			}
		}
		
	}
	reverse(s.begin(),s.end());
	cout<<s<<endl;
}
