#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

double area(double rot) {
    double big_angle = rot - acos(sqrt(2.0) / sqrt(3.0));
    double big_proj = sqrt((double) 3.0) * cos(big_angle);
    // cerr << big_proj << endl;

    double small_angle = rot - M_PI/2.0;
    double small_proj = 1.0 * cos(small_angle);
    // cerr << small_proj << endl;

    return sqrt((double) 2.0) * (small_proj + big_proj) * 0.5;
}

pair<double, double> rotat(pair<double, double> p, double rot) {
    return {p.first * cos(rot) - p.second * sin(rot), p.first * sin(rot) + p.second * cos(rot)};
}

void testcase() {
    // cout << area(0) << endl;
    // cout << rotat({1, 0}, M_PI/4).first << endl;

    double a;
    cin >> a;
    // cerr << a;

    double rot_l = 0;
    double rot_h = M_PI/2.0 - acos(sqrt(2.0) / sqrt(3.0));
    // cout << area(rot_h) << endl;

    while(abs(rot_h - rot_l) > 1e-11) {
        double rot_m = (rot_l + rot_h) / 2.0; 
        // cerr << area(rot_l) << " " << area(rot_m) << " " << area(rot_h) << endl;
        // cerr << a << endl;
        if(area(rot_m) < a) rot_l = rot_m;
        else rot_h = rot_m;
        // cout << rot_m << endl;
    }

    // cout << rot_l << endl;

    pair<double, double> x = {0.5 / sqrt(2.0), 0};
    pair<double, double> z = {-0.5 / sqrt(2.0), 0};
    pair<double, double> y = {0.0, 0.5};

    auto xp = rotat(x, rot_l);
    // auto yp = rotat(y, rot);
    auto zp = rotat(z, rot_l);
    auto yp = rotat(y, rot_l);

    // cerr << rot_l << endl;

    cout << endl;
    cout << xp.first << " " << xp.second << " " << 0.5/sqrt(2.0) << endl;
    cout << yp.first << " " << yp.second << " " << 0.0 << endl;
    cout << zp.first << " " << zp.second << " " << 0.5/sqrt(2.0) << endl;
}

int main() {
    int t;
    cin >> t;
    cout.precision(17);
    for(int i = 0; i < t; ++i) {
        cout << "Case #" << i + 1 << ": ";
        testcase();
    }
    /*
    cout << area(0.0) << endl;
    cout << area(0.1) << endl;
    cout << area(acos(sqrt(2.0) / sqrt(3.0))) << endl;
    cout << area(M_PI / 4 - acos(sqrt(2.0) / sqrt(3.0))) << endl;

    cout << M_PI / 2 - acos(sqrt(2.0) / sqrt(3.0)) << endl;

    for(double rot = 0; rot < M_PI/2.0; rot += 0.01) {
        cout << rot << " " << area(rot) << endl;
    }
    */
}
