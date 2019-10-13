#include <bits/stdc++.h>
using namespace std;
typedef long long intl;
void caso(intl n){
	vector <intl> digs;
	intl n1=n;
	while(n1>0){
		digs.push_back(n1%10);
		n1/=10;
	}
	
	reverse(digs.begin(),digs.end());
	vector <intl> ans;
	vector <intl> v(10,2);
	intl index=0;
	bool flag=false;
	for(intl i=0;i<intl(digs.size());i++){
		index=i;
		if(v[digs[i]]==0){
			for(intl j=digs[i]-1;j>=0;j--){
				if(v[j] >0){
					ans.push_back(j);
					v[j]--;
					flag=true;
					break;
				}
			}
			if(flag){
				break;
			}
			intl m=intl(ans.size());
			for(intl j=m-1;j>=0;j--){
				intl k=ans[j];
				v[k]++;
				ans.pop_back();
				for(intl l=k-1;l>=0;l--){
					if(v[l] >0){
						ans.push_back(l);
						v[l]--;
						
						flag=true;
						index=j;
						break;
					}
				}
				if(flag){
					break;
				}
			}
		}
		else{
			ans.push_back(digs[i]);
			v[digs[i]]--;
		}
		if(flag){
			break;
		}
	}
	
	for(intl i=index+1;i<intl(digs.size());i++){
		for(intl j=9;j>=0;j--){
			if(v[j]>0){
				v[j]--;
				ans.push_back(j);
				break;
			}
		}
	}
	intl ans1=0;
	intl exp=1;
	for(intl i=ans.size()-1;i>=0;i--){
		ans1+=exp*ans[i];
		exp*=10;
	}
	cout<<ans1<<endl;
}

int main(){
	intl in;
	while(cin>>in){
		caso(in);
	}
}
