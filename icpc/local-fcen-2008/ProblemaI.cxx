/*
 * ProblemaI.cxx
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
#include <algorithm>
using namespace std;
int X[10000], Inf[10000],Y[10000];
bool Caso(){
	int N;
	cin>>N;
	if(N == -1)
		return false;
	for(int i = 0;i<N;i++)
		scanf("%d",X+i);
	for(int i = 0;i<N;i++)
		scanf("%d",Y+i);
	sort(Y,Y+N);
	Inf[0] = X[1] - X[0];
	Inf[N-1] = X[N-1] - X[N-2];
	for(int i = 1;i<N-1;i++)
		Inf[i] = X[i+1] - X[i-1];
	sort(Inf,Inf+N);
	double R = 0;
	for(int i = 0;i<N;i++)
		R += double(Inf[i] * Y[i])/2.0;
	printf("%.1f\n",R);
	return true;
}
int main(int argc, char **argv)
{
	while(Caso());
	return 0;
}

