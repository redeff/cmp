
#include <iostream>
#include <vector>
#include <stdio.h>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <math.h>
using namespace std;
#define ll long long
bool check(vector<vector <int> > &v,int x,int y){ int sum=0; for(int i=x-1;i<x+2;i++){ for(int j=y-1;j<y+2;j++){ sum=sum+v[i][j]; } } if(sum==9){ return true; } return false; } int main(){ ll t; cin>>t; while(t>0){ int r; cin>>r; vector <vector <int> > v(71,vector <int> (5,0)); int x=2,y=2; for(int j=0;j<1000;j++){ cout<<x<<" "<<y<<endl; cout.flush(); int o,p; cin>>o>>p; if(o==-1&&p==-1){ break; } else if(o==0&&p==0){ break; } v[o][p]=1; if(check(v, x, y)){ x=x+3; } } t--; } return 0; }
