#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    ListNode *next;
    int val;
};

struct List {
    ListNode *head;
    ListNode *last;

    void merge(List b) {
        if(head == nullptr) {
            head = b.head;
            last = b.last;
        }

        last->next = b.head;
        last = b.last;
    }

    /*
    void push(int n) {
        ListNode* l = new ListNode {};
        l->next = nullptr;
        l->val = n;
        last->next = l;
        last = l;
    }
    */

    void pop() {
        if(head == last) {
            head = nullptr;
            last = nullptr;
        } else {
            auto t = head;
            head = head->next;
            delete t;
        }
    }

    List() {
        head = nullptr;
        last = nullptr;
    }

    List(int n) {
        ListNode* l = new ListNode {};
        l->next = nullptr;
        l->val = n;
        last = l;
        head = l;
    }
};

int main() {
    int n;
    cin >> n;

    vector<int> ns(n);

    for(int i = 0; i < n; ++i) {
        cin >> ns[i];
    }

    vector<List> xs;
    for(int i = 0; i < n; ++i) {
        if(xs.empty() || xs.back().last->val > ns[i]) {
            xs.push_back(List(ns[i]));
        } else {
            xs.back().merge(List(ns[i]));
        }
    }

    int times = 0;
    while(xs.size() > 1) {
        times++;
        vector<List> ns;
        ns.push_back(xs.front());
        for(int i = 1; i < xs.size(); ++i) {
            List l = xs[i];
            l.pop();
            if(l.head == nullptr) continue;
            else {
                if(l.head->val > ns.back().last->val) {
                    ns.back().merge(l);
                } else {
                    ns.push_back(l);
                }
            }
        }

        swap(ns, xs);
    }

    cout << times << endl;
}
