#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int counter = 0;
    int total = 0;
    // counter += s[0] == 'U' ? 1 : -1;
    for(int i = 0; i < n - 1; ++i) {
        counter += s[i] == 'U' ? 1 : -1;
        if(counter == 0 && s[i] == s[i + 1]) {
            total++;
        }
    }

    cout << total << endl;
}
