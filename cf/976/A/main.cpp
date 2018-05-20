#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    string bits;
    cin >> bits;

    if(bits == "0") {
        cout << "0" << endl;
        return 0;
    }
    
    cout << "1";
    for(char c : bits) if(c == '0') cout << "0";
    cout << endl;
}
