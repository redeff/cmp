// Segtree:
//  > .apply(a, b, k)
//  > .get(a, b)
//  > .construct(init)
template<class Ix, class Data, class Func, class Reduce, class Apply, class Compose>
// Reduce  = +
// Apply   = |>
// Compose = .
//
// Rules:
//     (a + b) + c  =  a + (b + c)          -- Associativity of +
//     (a . b) . c  =  a . (b . c)          -- Associativity of .
//   (a |> b) |> c  =  a |> (b . c)         -- Composition
//    (a + b) |> c  =  (a |> c) + (b |> c)  -- Distributivity of |> over +
struct SegTree {
    private:
        SegTree<Ix, Data, Func, Reduce, Apply, Compose> *left;
        SegTree<Ix, Data, Func, Reduce, Apply, Compose> *right;

        Data val;
        Func op;

        Data zero;
        Func id;

        Ix size;
        Ix n;

    public:
        SegTree(Ix nsize, Data nzero, Func nid) {
            size = nsize;
            n = size;

            zero = nzero;
            val = zero;

            id = nid;
            op = id;

            if(size == 1) {
                left = nullptr;
                right = nullptr;
            } else {
                left = new SegTree<Ix, Data, Func, Reduce, Apply, Compose>((size + 1) / 2, zero, id);
                right = new SegTree<Ix, Data, Func, Reduce, Apply, Compose>(size / 2, zero, id);
            }
        }

        Data gt(Ix bg, Ix ed) {
            if(bg <= 0 && ed >= size) {
                return Apply(val, op);
            } else if(ed <= 0 || bg >= n) {
                return zero;
            } else {
                // Else branch never happens if size == 1; so nullptr's don't get derreferenced

                return Apply(Reduce(
                            left->gt(bg, ed),
                            right->gt(bg - left->size, ed - left->size)),
                        op);
            }

        }

        void st(Ix bg, Ix ed, Func f) {
            if(bg <= 0 && ed >= size) {
                op = Compose(op, f);
            } else if(ed <= 0 || bg >= n) {
            } else {
                // Else branch never happens if size == 1; so nullptr's don't get derreferences

                // To ensure it works even if Compose isn't commutative
                left->op = Compose(left->op, op);
                right->op = Compose(right->op, op);
                op = id;

                left->st(bg, ed, f);
                right->st(bg - left->size, ed - left->size, f);

                val = Reduce(
                        Apply(left->val, left->op),
                        Apply(right->val, right->op));
            }

        }

        ~SegTree() {
            delete left;
            delete right;
        }
};
