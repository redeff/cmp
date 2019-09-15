#include "teams.h"
#include <bits/stdc++.h>
using namespace std;

#define fore(i, z, n) for(int i = z; i < int(n); ++i)

// Definen operacion
const int NEUTRO = 0;
int combine(int a,int b) { return a + b; }

struct Nodo
{
    Nodo *left, *right;
    int dato; // Datos
   
    void apply(int increment, int l, int r) // Aplica update
    {
        // lazy += increment;
        dato += increment * (r-l);
    }
    
    int query(int l, int r,int ql, int qr)
    {
        if (ql <= l && r <= qr) return dato;
        if (qr <= l || ql >= r) return NEUTRO;
        int mid = (l+r)/2;
        return combine(left->query(l,mid, ql, qr), right->query(mid, r, ql, qr));
    }
    
    Nodo* update(int l, int r,int ql, int qr, int increment)
    {
        if (ql <= l && r <= qr)
        {
            Nodo *ret = new Nodo(*this);
            ret->apply(increment, l, r);
            return ret;
        }
        if (qr <= l || ql >= r) return this;
        int mid = (l+r)/2;
        Nodo *ret  = new Nodo(*this);
        ret->left  = left->update(l,mid, ql, qr, increment);
        ret->right = right->update(mid, r, ql, qr, increment);
        ret->dato  = combine(ret->left->dato, ret->right->dato);
        return ret;
    }
    
    Nodo* singleUpdate(int l, int r,int index, int increment)
    {
        return update(l,r,index,index+1,increment);
    }
};

vector<Nodo*> st;

int SIZE = 1 << 20;

void init(int n, int a[], int b[]) {
	st.push_back(new Nodo);
	st.back()->dato = 0;
	st.back()->left = st.back();
	st.back()->right = st.back();
	vector<pair<int, int>> ns(n);
	fore(i, 0, n) ns[i] = {a[i], b[i]};
	sort(ns.begin(), ns.end());
	int pt = 0;
	fore(i, 0, n+10) {
		while(pt < ns.size() && ns[pt].first == i) {
			// cerr << "AAAH" << endl;
			st.back() = st.back()->singleUpdate(0, SIZE, ns[pt].second, 1);
			pt++;
		}
		st.push_back(st.back());
	}
}

int can(int m, int K[]) {
	Node *th = new Node;
	th->left = th;
	th->right = th;
	th-dato = 0;
	vector<int> extra;

	vector<int> ms(m);
	fore(i, 0, m) ms[i] = K[i];
	ms.push_back(0);
	++m;
	sort(ms.begin(), ms.end());

	// int carry = ms.front();
	// cerr << st[1]->query(0, SIZE, 2, 3) << " APA" << endl;
	/*
	if(carry > st[ms[0]]->query(0, SIZE, ms[0], SIZE)) {
		// cerr << "MUY FALSE" << endl;
		return false;
	}
	*/
	vector<pair<int, int>> left = {{0, 3000000}};
	fore(i, 1, m) {
	

		// int res = 
		// int res = st[ms[i-1]]->query(0, SIZE, ms[i-1], ms[i]);
		// cerr << "RES " << res << endl;
		//
		int lo = ms[i];
		int hi = SIZE;
		while(hi - lo > 1) {
			int mid = (hi + lo);
		}
		/*
		carry -= res;
		if(carry < 0) carry = 0;
		carry += ms[i];
		if(carry > st[ms[i]]->query(0, SIZE, ms[i], SIZE)) {
			// cerr << "FALSE " << i << " " << carry << endl;
			return false;
		}
		*/
	}

	return true;
}
