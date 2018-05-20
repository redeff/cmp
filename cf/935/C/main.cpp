#include <bits/stdc++.h>
using namespace std;

int main() {
    double r, xc, yc, xf, yf;
    cin >> r >> xc >> yc >> xf >> yf;

    xf -= xc;
    yf -= yc;

    cout << std::setprecision(15);

    if(sqrt(xf * xf + yf * yf) == 0) {
        cout << xc + r / 2 << " " << yc << " " << r / 2 << endl;
        return 0;
    } 

    double d = r / sqrt(xf * xf + yf * yf);
    if(d < 1) {
        cout << xc << " " << yc << " " << r << endl;
    } else {
        double xo = - xf * d;
        double yo = - yf * d;

        double xa = (xo + xf) / 2;
        double ya = (yo + yf) / 2;

        cout << xa + xc << " " << ya + yc << " " << sqrt((xa - xo) * (xa - xo) + (ya - yo) * (ya - yo)) << endl;

    }
}
