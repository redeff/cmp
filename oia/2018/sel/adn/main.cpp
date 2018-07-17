#include <string>
#include <bits/stdc++.h>

using namespace std;

int medir(string cad);

string secuenciar(int n, string s) {
    if(s == "AC") {
        int lo = 0;
        int hi = n + 1;
        while(lo < hi - 1) {
            int mid = (hi + lo) / 2;
            string t = "";
            for(int i = 0; i < mid; ++i) t.push_back('A');
            if(medir(t)) lo = mid; else hi = mid;
        }

        string t = "";
        for(int i = 0; i < lo; ++i) t.push_back('A');
        for(int i = lo; i < n; ++i) t.push_back('C');
        return t;
    } else return "";
    ``
}
