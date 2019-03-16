/*
 * ProblemaA.cxx
 * 
 * Copyright 2019 Unknown <reedef@reedef-pc>
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
using namespace std;
bool Case()
{
	string A,B;
	cin>>A>>B;
	if(A=="*" && B=="*")
		return false;
	A = " " + A, B = " " + B;
	int La = A.size(), Lb = B.size();
	vector<vector<int> > cost(La+1,vector<int>(Lb+1,1e7));
	for(int i = 0;i<=La;i++)
		cost[i][0] = i;
	for(int i = 0;i<=Lb;i++)
		cost[0][i] = i;
	for(int i = 1;i<La;i++)
		for(int j = 1;j<Lb;j++)
		{
			if(A[i] == B[j])
				cost[i][j] = min(cost[i-1][j-1],cost[i][j]);
			else
				cost[i][j] = min(cost[i-1][j-1]+1,cost[i][j]);
			cost[i][j] = min(cost[i-1][j]+1,cost[i][j]);
			cost[i][j] = min(cost[i][j-1]+1,cost[i][j]);
			for(int k = 1;k<j;k++)
				if(A[i] == B[j-k] && A[i-1] == B[j])
				{
					int c = cost[i-1][k-1] + j-k;
					cost[i][j] = min(cost[i][j],c);
				}
			for(int k = 1;k<i;k++)
				if(A[i-k] == B[j] && A[i] == B[j-1])
				{
					int c = cost[k-1][j-1] + i-k;
					cost[i][j] = min(cost[i][j],c);
				}
			
			//cout<<i<<" - "<<j<<" = "<<cost[i][j]<<endl;
		}
	cout<<cost[La-1][Lb-1]<<endl;
	return true;
}
int main(int argc, char **argv)
{
	//Case();
	while(Case());
	return 0;
}

