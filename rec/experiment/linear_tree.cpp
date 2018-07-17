#include<bits/stdc++.h>
using namespace std;

template<class T>
struct Node {
    int parent;
    T value;
    int left;
    int right;
};

template<class T>
struct Tree {
    vector<Node<T>> ns;
    void put(T val) {
        if(ns.size() == 0) {
            ns.push_back(Node<T> {.parent = -1, .value = val, .left = -1, .right = -1 });
            return;
        }
        int i = 0;
        while(true) {
            if(ns[i].value < val) {
                if(ns[i].right != -1) {
                    // assert(ns[i].right > i);
                    i = ns[i].right;
                }
                else break;
            }
            else if(ns[i].value > val) {
                if(ns[i].left != -1) {
                    // assert(ns[i].left > i);
                    i = ns[i].left;
                }
                else break;
            }
            else return;
        }
        ns.push_back(Node<T> {.parent = i, .value = val, .left = -1, .right = -1 });
        if(ns[i].value > val) ns[i].left = ns.size() - 1;
        else ns[i].right = ns.size() - 1;
    }

    void take(T val) {
        int i = 0;
        while(i != -1) {
            if(ns[i].value < i) {
                i = ns[i].right;
            }
            else if(ns[i].value > i) {
                i = ns[i].left;
            }
            else break;
        }

        if(i != -1) {
            if(ns[ns.back().parent].value < ns.back().value) {
                ns[ns.back().parent].right = i; 
            }
            else {
                ns[ns.back().parent].left = i;
            }
            // TODO
            ns[i] = ns.back();
            ns.pop_back();
        }
    }
};

int main() {
    // Tree<int> tree;
    std::unordered_set<int> tree;
    for(int i = 0; i < 1000000; ++i) {
        // tree.put(rand() % 100000000);         
        tree.insert(rand() % 100000000);         
    }
}
