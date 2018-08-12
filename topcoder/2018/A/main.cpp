#include <string>
#include <vector>

string to_desc(int k) {
    if(k <= 4) return "Few";
    if(k <= 9) return "Several";
    if(k <= 19) return "Pack";
    if(k <= 49) return "Lots";
    if(k <= 99) return "Horde";
    if(k <= 249) return "Throng";
    if(k <= 499) return "Swarm";
    if(k <= 999) return "Zounds";
    return "Legion";
}

int min_val(string k) {
    if(k == "Few") return 1;
    if(k == "Several") return 5;
    if(k == "Pack") return 10;
    if(k == "Lots") return 20;
    if(k == "Horde") return 50;
    if(k == "Throng") return 100;
    if(k == "Swarm") return 250;
    if(k == "Zounds") return 500;
    if(k == "Legion") return 1000;
}

int max_val(string k) {
    if(k == "Few") return 4;
    if(k == "Several") return 9;
    if(k == "Pack") return 19;
    if(k == "Lots") return 49;
    if(k == "Horde") return 99;
    if(k == "Throng") return 249;
    if(k == "Swarm") return 499;
    if(k == "Zounds") return 999;
    if(k == "Legion") return 1000;
}


struct ArmySize {
    vector <string> getSum(vector <string> units) {
        int mn = 0;
        int mx = 0;
        for(string s : units) {
            mn += min_val(s);
            mx += max_val(s);
        }

        vector<string> poss;

        for(int i = mn; i <= mx; ++i) {
            string t = to_desc(i);
            if(poss.empty() || poss.back() != t) poss.push_back(t);
        }

        return poss;
    }
};
