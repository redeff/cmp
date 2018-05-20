#include <bits/stdc++.h>
using namespace std;

int main() {
    regex frnd("(ch)|(he)|(ef)");

    int n;
    int total = 0;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        string name;
        cin >> name;

        if(regex_search(name, frnd)) total++;
    }

    cout << total << endl;
}
