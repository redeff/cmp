#include <bits/stdc++.h>
using namespace std;

class MtGFight {
    vector<int> findGoodFight(vector<int> a, vector<int> b) {
        for(int i = 0; i < a.size(); ++i) {
            for(int j = 0; j < a.size(); ++j) {
                if(a[i] >= b[j] && b[i] > a[j]) {
                    return {i, j};
                }
            }
        }
        return {};
    }
}
