#include <bits/stdc++.h>
using namespace std;

const int bound = 1000001;

int main() {
    int n;
    cin >> n;
    vector<int> cows(n);
    vector<int> nums(bound, 0);
    for(int i = 0; i < n; ++i) {
        cin >> cows[i];
        nums[cows[i]]++;
    }
    vector<int> pats(bound, 0);

    // Esto es O(n H_n) = O(n ln n)
    for(int i = 1; i < bound; ++i) {
        for(int k = i; k < bound; k += i) {
            pats[k] += nums[i];
        }
    }

    for(int i = 0; i < n; ++i) {
        cout << pats[cows[i]] - 1 << endl;
    }
}
