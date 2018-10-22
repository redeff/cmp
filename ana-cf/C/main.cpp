#include <bits/stdc++.h>
using namespace std;

string to_date(int sec) {
    string s;
    s.push_back(sec / 600 + '0');
    sec -= sec / 600 * 600;
    s.push_back(sec / 60 + '0');
    sec -= sec / 60 * 60;
    s.push_back(':');
    s.push_back(sec / 10 + '0');
    sec -= sec / 10 * 10;
    s.push_back(sec + '0');

    return s;
}

int to_int(string s) {
    int out = 0;
    out += s[4] - '0';
    out += 10 * (s[3] - '0');
    out += 60 * (s[1] - '0');
    out += 600 * (s[0] - '0');

    return out;
}

int main() {
    string a;
    string b;
    cin >> a >> b;

    int ia = to_int(a);
    int ib = to_int(b);
    cout << to_date(((ia - ib) + 1440) % 1440) << endl;
}
