// LeafTree:
//  > .nth_leaf(Ix i):
//    get index of nth leaf
//  > .parent(Ix i):
//    get parent of a node
//  > .left
//  > .right
//  > .is_leaf
template<class Ix, class Data>
struct LeafTree {
    
};

template<class Ix>
struct Index {
    Ix ix;
    Ix size; 
    Index(Ix ix, Ix size): ix(ix), size(size) {}

    bool is_leaf() {
        return ix % 2 == 0;
    }
}
