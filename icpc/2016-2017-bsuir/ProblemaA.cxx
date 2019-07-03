#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    double a,b,c;
    cout.precision(11);
	
    cin>>a>>b;
    c = (a+b)/(2.0*(2-a-b));
    if(a == 0 || b == 0)
		cout<<0<<endl;
	else if(a == 1 || b == 1)
		cout<<1<<endl;
	else
		cout<<c<<endl;
	//printf("%.5f",c);
    return 0;
}
