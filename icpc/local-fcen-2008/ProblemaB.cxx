/*
 * ProblemaB.cxx
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
#include <cstdio>
using namespace std;
void Caso(int tengo[4], int cuesta[4], int compro[4])
{
	int MinC = 0;
	for(int i = 0;i<4;i++)
	{
		int C = tengo[i] / cuesta[i] + bool(tengo[i]%cuesta[i]);
		MinC = max(MinC,C);
	}
	for(int i = 0;i<4;i++)
		compro[i] = MinC*cuesta[i] - tengo[i];
	
}
int tengo[4], cuesta[4], compro[4];
int main(int argc, char **argv)
{
	while(true)
	{
		for(int i = 0;i<4;i++)
			scanf("%d",tengo+i);
		for(int i = 0;i<4;i++)
			scanf("%d",cuesta+i);
		if(tengo[0] == -1)
			return 0;
		Caso(tengo,cuesta,compro);
		for(int i = 0;i<4;i++)
			printf("%d ",compro[i]);
		printf("\n");
	}
	return 0;
}

