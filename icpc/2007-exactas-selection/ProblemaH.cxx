/*
 * Problema H.cxx
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
using namespace std;
bool Case()
{
	string A,B;
	cin>>A>>B;
	if(A == "*")
		return false;
	//cout<<A.size()<<" vs "<<B.size()<<endl;
	if(A.size() > B.size())
		B = string(A.size()-B.size(),'0') + B;
	else if(B.size() > A.size())
		A = string(B.size() - A.size(),'0') + A;
	if(A > B)
		cout<<">"<<endl;
	else if(A<B)
		cout<<"<"<<endl;
	else
		cout<<"="<<endl;
	return true;
}
int main(int argc, char **argv)
{
	while(Case());
}

