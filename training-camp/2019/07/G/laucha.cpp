/*
 * Problema7G.cxx
 * 
 * Copyright 2019 Visita <visita@lab07>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
int mkx[] = {-2,-2,-1,1,2,2,1,-1};
int mky[] = {-1,1,2,2,1,-1,-2,-2};

int mrx[] = {0,1,0,-1};
int mry[] = {1,0,-1,0};

int mbx[] = {1,1,-1,-1};
int mby[] = {1,-1,-1,1};

//int DP[8][8][8][8][8][8][3]; /// Knight X,Y ; Rook (Torre) X,Y ; Bishop (Alfil) X,Y; 
bool EsLegal(int x, int y)
{
	return (0<=x && x<=7 && 0<=y && y<= 7);
}
int obkx, obky, obrx, obry, obbx, obby;
int ID[8][8][8][8][8][8][3], gid = 0;
vector<int> Ary[3000000];  /// Knight X,Y ; Rook (Torre) X,Y ; Bishop (Alfil) X,Y; 
int Dist[3000000];

bool MovLinea(int & ax, int & ay, int bx, int by, int cx, int cy, int mx, int my)
{
	ax = ax + mx, ay = ay + my;
	if(ax<0 || ax > 7 || ay < 0 || ay > 7)
		return false;
	if(ax == bx && ay == by)
		return false;
	if(ax == cx && ay == cy)
		return false;
	return true;
}
struct pos{
	int kx,  ky,  rx,  ry,  bx, by, play;
	void Leer(int _kx, int _ky, int _rx, int _ry, int _bx, int _by, int _play)
	{
		kx = _kx, ky = _ky;
		rx = _rx, ry = _ry;
		bx = _bx, by = _by;
		play = _play;
	}
	void Mostrar()
	{
		cout<<kx<<" , "<<ky<<" : "<<rx<<" , "<<ry<<" : "<<bx<<" , "<<by<<" ||| "<<play<<endl;
	}
};
pos rev[3000000];
void Armar_Grafo()
{
	//vector<pos> iterative;
	//queue<pos> QQ;
	//pos a(kx,ky,rx,ry,bx,by,play);
	//QQ.push(a);
	for(int kx = 0;kx<7;kx++)
		for(int ky = 0;ky<7;ky++)
			for(int rx = 0;rx<7;rx++)
				for(int ry = 0;ry<7;ry++)
					for(int bx = 0;bx<7;bx++)
						for(int by = 0;by<7;by++)
							for(int play = 0;play<3;play++)
								ID[kx][ky][rx][ry][bx][by][play] = gid, rev[gid].Leer(kx,ky,rx,ry,bx,by,play),gid++;
	for(int kx = 0;kx<7;kx++)
		for(int ky = 0;ky<7;ky++)
			for(int rx = 0;rx<7;rx++)
				for(int ry = 0;ry<7;ry++)
					for(int bx = 0;bx<7;bx++)
						for(int by = 0;by<7;by++)
							for(int play = 0;play<3;play++)
							{
								if(kx == bx && ky == by)
									continue;
								if(kx == rx && ky == ry)
									continue;
								if(rx == bx && ry == by)
									continue;
								//if(ID[kx][ky][rx][ry][bx][by][play] > 0)
								//{
								//	return ID[kx][ky][rx][ry][bx][by][play] ;
								//}
								int lid = ID[kx][ky][rx][ry][bx][by][play];
								//ID[kx][ky][rx][ry][bx][by][play] = gid++;
								//cout<<kx<<" ; "<<ky<<" ; "<<rx<<" ; "<<ry<<" ; "<<bx<<" ; "<<by<<" ; "<
								if(play == 0)
								{
									for(int k = 0;k<8;k++)
									{
										int nkx = kx + mkx[k];
										int nky = ky + mky[k];
										if(EsLegal(nkx,nky) && ((nkx!=rx||nky!=ry) && (nkx!=bx||nky!=by)))
										{
											int nid = ID[nkx][nky][rx][ry][bx][by][1];
											Ary[lid].push_back(nid);
										}
									}
								}
								if(play == 1)
								{
									for(int k = 0;k<4;k++)
									{
										int lrx = rx, lry = ry;
										while(MovLinea(lrx,lry,kx,ky,bx,by,mrx[k],mry[k]))
										{
											int nid = ID[kx][ky][lrx][lry][bx][by][1];
											Ary[lid].push_back(nid);
										}
									}
								}
								if(play == 2)
								{
									for(int k = 0;k<4;k++)
									{
										int lbx = bx, lby = by;
										while(MovLinea(lbx,lby,kx,ky,rx,ry,mbx[k],mby[k]))
										{
											int nid = ID[kx][ky][rx][ry][lbx][lby][1];
											Ary[lid].push_back(nid);
										}
									}
								}
							}
							
	/*while(iterative.size())
	{
	{
		//cout<<gid<<" = "<<kx<<" , "<<ky<<" : "<<rx<<" , "<<ry<<" : "<<bx<<" , "<<by<<" ||| "<<play<<endl;
		//if(kx == obkx && ky == obky && rx == obrx && ry == obry && bx == obbx && by == obby)
		//	return 0;
		if(ID[kx][ky][rx][ry][bx][by][play] > 0)
		{
			return ID[kx][ky][rx][ry][bx][by][play] ;
		}
		int lid = gid;
		ID[kx][ky][rx][ry][bx][by][play] = gid++;
		//cout<<kx<<" ; "<<ky<<" ; "<<rx<<" ; "<<ry<<" ; "<<bx<<" ; "<<by<<" ; "<
		if(play == 0)
		{
			for(int k = 0;k<8;k++)
			{
				int nkx = kx + mkx[k];
				int nky = ky + mky[k];
				if(EsLegal(nkx,nky) && ((nkx!=rx||nky!=ry) && (nkx!=bx||nky!=by)))
				{
					int nid = DFS(nkx,nky,rx,ry,bx,by,1);
					Ary[lid].push_back(nid);
				}
			}
		}
		if(play == 1)
		{
			for(int k = 0;k<4;k++)
			{
				int lrx = rx, lry = ry;
				while(MovLinea(lrx,lry,kx,ky,bx,by,mrx[k],mry[k]))
				{
					int nid = DFS(kx,ky,lrx,lry,bx,by,2);
					Ary[lid].push_back(nid);
				}
			}
		}
		if(play == 2)
		{
			for(int k = 0;k<4;k++)
			{
				int lbx = bx, lby = by;
				while(MovLinea(lbx,lby,kx,ky,rx,ry,mbx[k],mby[k]))
				{
					int nid = DFS(kx,ky,rx,ry,lbx,lby,0);
					Ary[lid].push_back(nid);
				}
			}
		}
		return ID[kx][ky][rx][ry][bx][by][play];
	}*/
}
void Caso()
{
	int kx,ky,rx,ry,bx,by;
	cin>>kx>>ky>>rx>>ry>>bx>>by;
	if((rx+rx)%2!=(bx+by)%2)
	{
		cout<<-1<<endl;
		return;
	}
	int ini = ID[kx][ky][rx][ry][bx][by][0];
	int fin0 = ID[bx][by][kx][ky][rx][ry][0];
	int fin1 = ID[bx][by][kx][ky][rx][ry][1];
	int fin2 = ID[bx][by][kx][ky][rx][ry][2];
	memset(Dist,0,sizeof(Dist));
	queue<int> Q;
	Q.push(ini);
	while(Q.size())
	{
		int n = Q.front();
		Q.pop();
		//if(Dist[n] == 0)
		//	continue;
		int d = Dist[n]+1, L = Ary[n].size();
		cout<<n<<" => "<<d<<endl;
		rev[n].Mostrar();
		for(int i = 0;i<L;i++)
		{
			int k = Ary[n][i];
			if(d < Dist[k] || Dist[k] == 0)
				Dist[k] = d, Q.push(k);
		}
	}
	// cout<<fin0<<" = "<<Dist[fin0]<<endl;
	// cout<<fin1<<" = "<<Dist[fin1]<<endl;
	// cout<<fin2<<" = "<<Dist[fin2]<<endl;
	int d = Dist[fin0];
	if(Dist[fin1]!=0 && (Dist[fin1] < d || d == 0))
		d = Dist[fin1];
	if(Dist[fin2]!=0 && (Dist[fin2] < d || d == 0))
		d = Dist[fin2];
	
	cout<<min(Dist[fin0],min(Dist[fin1],Dist[fin2]))<<endl;
}
int main(int argc, char **argv)
{
	memset(ID,0,sizeof(ID));
	Armar_Grafo();
	//DFS(0,0,7,7,1,1,0);
	//DFS(0,0,7,7,1,0,0);
	// cout<<"K"<<endl;
	int T;
	cin>>T;
	while(T--)
		Caso();
	return 0;
}
