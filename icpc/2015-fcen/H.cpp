#include <bits/stdc++.h>
using namespace std;

int frente[110];
pair<int,int> inter[110];
/// Rotar
bool Inter(pair<int,int> A, pair<int,int> B)
{
	int ini = max(A.first,B.first);
	int fin = min(A.second,B.second);
	return fin>ini;
}
int Contar(vector<vector<int> > &in)
{
	int N = int(in.size())-2, M = int(in[0].size())-2; 
	int Cant = 0;
	for(int i = 0;i<110;i++)
	{
		inter[i] = {0,0};
		frente[i] = 0;
	}
	for(int i = 1;i<=N+1;i++)
	{
		inter[0] = {0,0};
		for(int j = 1;j<=M;j++)
		{
			if(in[i][j] >= in[i-1][j])
				inter[j] = {0,0};
			else
			{
				inter[j] = {in[i][j],in[i-1][j]};
				if(!Inter(inter[j-1],inter[j]))
					Cant++;
			}
		}
		
	}
	return Cant;
}
#define forn(i,n) for(int i = 0;i<int(n);i++)
vector<vector<int>> rot(vector<vector<int>> &mat) {
	int n = int(mat.size());
	int m = int(mat[0].size());
	vector<vector<int>> out(m, vector<int>(n));
	forn(i, m) forn(j, n) {
		out[i][j] = mat[n - j - 1][i];
	}
	return out;
}
bitset<200> used[200];
int mx[4] = {1,0,-1,0}, my[4] = {0,1,0,-1};
void DFS(int i, int j, int alt, vector<vector<int> > & mat)
{
	
	if(i==-1 || i==int(mat.size())) return;
	if(j==-1 || j==int(mat[0].size())) return;
	if(mat[i][j] != alt) return;
	if(used[i][j]) return;
	used[i][j] = true;
	for(int k = 0;k<4;k++)
		DFS(i+my[k],j+mx[k], alt, mat);
}
int Caso(int N, int M)
{
	for(int i = 0;i<200;i++) used[i].reset();
	vector<vector<int> > in(N+2,vector<int>(M+2,0));
	for(int i = 1;i<=N;i++)
		for(int j = 1;j<=M;j++)
			scanf("%d",&in[i][j]);
	int RES = 1;
	for(int i = 0;i<4;i++)
	{
		int c = Contar(in);
		//cout<<"Rotacion "<<i<<" tiene "<<c<<endl;
		RES+=c, in = rot(in);
		//cout<<endl;
		//for(auto k : in)
		{
			//cout<<endl;
			//for(auto j : k) cout<<j<<" ";
		}
	}
	for(int i = 1;i<=N;i++)
		for(int j = 1;j<=M;j++)
		{
			if(!used[i][j])
			{
				RES++;
				DFS(i,j,in[i][j],in);
			}
		}
	return RES;
}
int main()
{
	int N,M;
	while(cin>>N>>M)cout<<Caso(N,M)<<endl;
}
