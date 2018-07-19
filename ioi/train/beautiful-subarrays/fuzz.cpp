#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    assert(argc > 2);
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    cout << n << " " << k << endl;
    for(int i = 0; i < n; ++i) {
        cout << rand() % ((int) 10e9) << " ";
    }
    cout << endl;
}
