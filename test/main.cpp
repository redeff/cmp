#include <bits/stdc++.h>
using namespace std;

int high_prime(int n) {
    int hi = -1;
    for(int i = 2; i * i <= n; ++i) {
        while(n % i == 0) {
            hi = i;
            n /= i;
        } 
    }

    return max(hi, n);
}
int main() {
    int n = 200000;
    long long int total;
    for(int i = 2; i < n; ++i) {
        total += (long long int) n/high_prime(i);
    }

    cout << total << endl;
}
