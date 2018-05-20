#include <bits/stdc++.h>
using namespace std;

bool test(string s) {
    if(s[0] != 'a') return false;
    if(s.back() != 'c') return false;
    for(int i = 1; i < s.size(); ++i) {
        if(s[i] != s[i - 1]) {
            if(s[i - 1] == 'a' && s[i] == 'b' || s[i - 1] == 'b' && s[i] == 'c') {
            } else return false;
        }
    }

    int numa = 0;
    int numb = 0;
    int numc = 0;

    for(char c  : s) {
        if(c == 'a') numa++;
        else if(c == 'b') numb++;
        else if(c == 'c') numc++;
    }

    return numc == numa || numc == numb;
}

int main() {
    string s;
    cin >> s;
    if(test(s)) {
       cout << "YES" << endl;
    } else {
       cout << "NO" << endl;
    } 
}
