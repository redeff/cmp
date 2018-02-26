// And so it begins
//
// Right = Clockwise
// Right = Counter clockwise

// This datastructure represents a circularly linked list
// Each element is in one of several disjoint sets repre-
// sented by its color
struct LinkedList {

    // The next and previous elements in the list
    LinkedList *left_list;
    LinkedList *right_list;

    // The next and previous elements in the list
    // that are the same color as curr element
    LinkedList *left_set;
    LinkedList *right_set;

    // The extremes of a given color C are a pair of
    // elements in the list such that:
    //  a) There's no element of color C between
    //     those elements in clockwise order
    //
    //  b) It's the widest pair with such a property
    LinkedList *left_extreme;
    LinkedList *right_extreme;

    int color;

    // It is guaranteed that this->index < this->left_list.index,
    // except for a single element in the entire list
    int index;
}

bool is_in(int a, int b, int x) {

}

// The most important function
void rec_join_subsets(LinkedList ns) {
    LinkedList left_ptr;
    LinkedList right_ptr;

    LinkedList left_bound;
    LinkedList right_bound;


}
