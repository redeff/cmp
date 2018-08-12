#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll INF = 33333333333333333ll;

ll calc(vector<int> cs, vector<int> as, vector<int> bs) {
    sort(cs.begin(), cs.end());
    if(as.size() < 50) return INF;
    if(bs.size() < 50) return INF;

    set<int> sumset;
    for(int a : as) if(a > 5000 || a < 1) return INF;
        else for(int b : bs) if(b > 5000 || b < 1) return INF;
            else sumset.insert(a + b);

    vector<int> sum(sumset.begin(), sumset.end());

    if(sum.size() < cs.size()) return INF;
    int d = sum.size() - cs.size();
    ll total = 0;
    for(int i = 0; i <= d; ++i) {
        for(int j = 0; j < cs.size(); ++j) {
            total += (ll) abs(cs[j] - sum[j + i]);
        }
    }

    return total;
}

const ll each = 50;

vector<pair<int, int>> distribute(vector<int> &cs) {
    int c = cs.size();
    assert(c >= 2 * each - 1);

    int k = (c - 50) / 49;
    assert(k > 0);

    vector<pair<int, int>> out;

    for(int i = 0; i < k; ++i) {
        out.emplace_back((c * i) / k, (c * (i + 1)) / k - (c * i) / k);
    }

    return out;

    /*
    vector<int> iot(c);
    for(int i = 0; i < c; ++i) iot[i] = i;

    sort(iot.begin(), iot.end(), [&](int a, int b) {
        int al = max(a - each/2, 0);
        int ah = min(a + each/2, c - 1);

        int bl = max(b - each/2, 0);
        int bh = min(b + each/2, c - 1);
        return (c[ah] - c[al]) * (bh - bl) < (c[bh] - c[bl]) * (ah - al);
    });

    vector<bool> chosen(c, false);
    */
}

pair<vector<int>, vector<int>> cont_ref(vector<int> cs) {
    int c = cs.size();
    unordered_set<int> csu; 
    for(int ci = 0; ci < cs.size(); ++ci) {
        csu.insert(cs[ci]);
    }

    while(csu.size() < 2 * each - 1) {
        csu.insert(rand() % 5000 + 1);
    }
    c = csu.size();
    /*
    for(int i = 1; c < 2 * each - 1; ++i) {
        if(csu.count(i) == 0) {
            csu.insert(i);
            c++;
        }
    }
    */

    cs.clear();
    copy(csu.begin(), csu.end(), back_inserter(cs));
    sort(cs.begin(), cs.end());

    auto d = distribute(cs);
    vector<int> st(d.size());
    for(int i = 0; i < d.size(); ++i) {
        int median = cs[d[i].first + d[i].second/2];
        st[i] = median - d[i].second/2;
    }

    if(st[0] <= 0) st[0] = 1;

    for(int i = 0; i < d.size() - 1; ++i) {
        if(st[i] + d[i].second > st[i + 1]) {
            st[i + 1] = st[i] + d[i].second;
        }
    }

    if(st.back() + d.back().second > 5000) st.back() = 5000 - d.back().second;

    for(int i = d.size(); i > 0; --i) {
        if(st[i - 1] + d[i - 1].second > st[i]) {
            st[i - 1] = st[i] - d[i - 1].second;
        }
    }

    vector<int> as;
    for(int i = 0; i < d.size(); ++i) {
        for(int k = 0; k < d[i].second - each + 1; ++k) as.push_back(st[i] + k);
    }

    vector<int> bs;
    for(int i = 1; i <= 50; ++i) bs.push_back(i);

    return {as, bs};
}
pair<vector<int>, vector<int>> cont(vector<int> cs) {
    int c = cs.size();
    unordered_set<int> csu; 
    for(int ci = 0; ci < cs.size(); ++ci) {
        csu.insert(cs[ci]);
    }

    while(csu.size() < 2 * each - 1) {
        csu.insert(rand() % 5000 + 1);
    }
    c = csu.size();
    /*
    for(int i = 1; c < 2 * each - 1; ++i) {
        if(csu.count(i) == 0) {
            csu.insert(i);
            c++;
        }
    }
    */

    cs.clear();
    copy(csu.begin(), csu.end(), back_inserter(cs));
    sort(cs.begin(), cs.end());

    // c >= 2 * each + 1

    ll num = (c - (2 * each - 1)) / each;
    ll fst = c - each * num;

    // 1              -> each
    // fst - each + 1 -> fst

    ll fsta = fst - each + 1;

    vector<ll> as;
    as.push_back(max(cs[fst/2ll] - fst/2ll - 1 + fsta, fsta));
    ll ptr = fst;
    for(ll i = 0; i < num; ++i) {
        ll na = cs[ptr + each/2ll] - each/2ll;
        na = max(na, as.back() + each);
        as.push_back(na);
        ptr += each;
    }

    for(int ai = as.size() - 1; ai > 0; --ai) {
        if(as[ai] < as[ai - 1] + each) {
            as[ai - 1] = as[ai] - each;
        }
    }

    vector<int> asf;
    // cout << as.size() + fsta - 1 << endl;

    for(int i = as.front() - fsta + 1; i < as.front(); ++i) asf.push_back(i);
    for(int ae : as) asf.push_back(ae);

    vector<int> bsf;
    for(int i = 0; i < 50; ++i) {
        bsf.push_back(i + 1);
    }

    return {asf, bsf};
}

pair<vector<int>, vector<int>> cont2(vector<int> cs) {
    int c = cs.size();
    unordered_set<int> csu; 
    for(int ci = 0; ci < cs.size(); ++ci) {
        csu.insert(cs[ci]);
    }

    while(csu.size() < 2 * each - 1) {
        csu.insert(rand() % 5000 + 1);
    }
    c = csu.size();
    /*
    for(int i = 1; c < 2 * each - 1; ++i) {
        if(csu.count(i) == 0) {
            csu.insert(i);
            c++;
        }
    }
    */

    cs.clear();
    copy(csu.begin(), csu.end(), back_inserter(cs));
    sort(cs.begin(), cs.end());

    auto d = distribute(cs);
    vector<int> st(d.size());
    for(int i = 0; i < d.size(); ++i) {
        int median = cs[d[i].first + d[i].second/2];
        st[i] = median - d[i].second;
    }

    if(st[0] <= 0) st[0] = 1;

    for(int i = 0; i < d.size() - 1; ++i) {
        if(st[i] + 2 * d[i].second - 1 > st[i + 1]) {
            st[i + 1] = st[i] + 2 * d[i].second - 1;
        }
    }

    if(st.back() > 5000) st.back() = 5000;

    for(int i = d.size(); i > 0; --i) {
        if(st[i - 1] + 2 * d[i - 1].second - 1 > st[i]) {
            st[i - 1] = st[i] - 2 * d[i - 1].second + 1;
        }
    }

    vector<int> as;
    for(int i = 0; i < d.size(); ++i) {
        for(int k = 0; k < d[i].second - each + 1; ++k) as.push_back(st[i] + 2 * k);
    }

    vector<int> bs;
    for(int i = 1; i <= 50; ++i) bs.push_back(i);

    return {as, bs};
}

/*
pair<vector<int>, vector<int>> cont2(vector<int> cs) {
    int c = cs.size();
    unordered_set<int> csu; 
    for(int ci = 0; ci < cs.size(); ++ci) {
        csu.insert(cs[ci]);
    }

    for(int i = 1; c < 2 * each - 1; ++i) {
        if(csu.count(i) == 0) {
            csu.insert(i);
            c++;
        }
    }

    cs.clear();
    copy(csu.begin(), csu.end(), back_inserter(cs));
    sort(cs.begin(), cs.end());

    // c >= 2 * each + 1

    ll num = (c - (2 * each - 1)) / each;
    ll fst = c - each * num;

    // 1              -> each
    // fst - each + 1 -> fst

    ll fsta = fst - each + 1;

    vector<ll> as;
    as.push_back(max(cs[fst/2ll] - fst/2ll - 1 + fsta, 2 * fsta + 1));
    ll ptr = fst;
    for(ll i = 0; i < num; ++i) {
        ll na = cs[ptr + each/2ll] - each;
        na = max(na, as.back() + 2 * each);
        as.push_back(na);
        ptr += each;
    }

    for(int ai = as.size() - 1; ai > 0; --ai) {
        if(as[ai] < as[ai - 1] + 2 * each) {
            as[ai - 1] = as[ai] - each;
        }
    }

    vector<int> asf;
    // cout << as.size() + fsta - 1 << endl;

    for(int i = as.front() - 2 * fsta + 1; i < as.front(); i += 2) asf.push_back(i);
    for(int ae : as) asf.push_back(ae);

    vector<int> bsf;
    for(int i = 0; i < 50; ++i) {
        bsf.push_back(2 * i + 1);
    }

    return {asf, bsf};
}
*/


pair<vector<int>, vector<int>> randomized(vector<int> cs) {
    int n = 5000;
    int s = cs.size();
    int k = floor(log(1 - s/n)/log((n-1)/n));
    int av = cs[cs.size() / 2];
    av--;
    vector<int> as;
    vector<int> bs;
    for(int i = 0; i < k; ++i) {
        as.push_back(rand() % av + 1);
        bs.push_back(rand() % av + 1);
    }

    return {as, bs};
}

pair<vector<int>, vector<int>> trivial(vector<int> cs) {
    int n = cs.size();

    sort(cs.begin(), cs.end());
    int median = cs[n/2];
    median /= 2;

    // ll siz = max(100ll, n + 2);
    int a = max(50, (n + 1) / 2);
    int b = max(50, (n + 2) / 2);

    unordered_set<int> as;
    unordered_set<int> bs;


    int loa = median + 1 - a/2;
    int hia = median + a - a/2;
    if(loa < 1) {
        hia += 1 - loa;
        loa = 1;
    }
    if(hia > 5000) {
        loa -= hia - 5000;
        hia = 5000;
    }

    for(int i = loa; i <= hia; ++i) {
        as.insert(i);
    }

    int lob = median + 1 - b/2;
    int hib = median + b - b/2;
    if(lob < 1) {
        hib += 1 - lob;
        lob = 1;
    }
    if(hib > 5000) {
        lob -= hib - 5000;
        hib = 5000;
    }

    for(int i = lob; i <= hib; ++i) {
        bs.insert(i);
    }

    vector<int> asf(as.begin(), as.end());
    vector<int> bsf(bs.begin(), bs.end());

    return {asf, bsf};
}

int main() {
    ll c;
    cin >> c;
    vector<int> cs(c);
    for(int i = 0; i < c; ++i) {
        cin >> cs[i]; 
    }

    sort(cs.begin(), cs.end());

    // auto o1 = cont(cs);
    auto o2 = cont2(cs);
    // auto o2 = trivial(cs);
    /*
    auto o3 = o1;
    o3.second = vector<int>(50, 0);
    for(int i = 0; i < 50; ++i) {
        o3.second[i] = 2 * i + 1;
    }
    */
    auto o1 = cont_ref(cs);

    /*
    ll w1 = calc(cs, o1.first, o1.second);
    ll w2 = calc(cs, o2.first, o2.second);
    // ll w3 = calc(cs, o3.first, o3.second);

    // auto &p = w1 < w2 ? (w3 < w1 ? o3 : o1) : (w3 < w2 ? o3 : o2);
    auto &p = w1 < w2 ? o1 : o2;
    */
    auto &p = o1;

    cout << p.first.size() << endl;
    for(int i : p.first) cout << i << " ";
    cout << endl;

    cout << p.second.size() << endl;
    for(int i : p.second) cout << i << " ";
    cout << endl;
}
