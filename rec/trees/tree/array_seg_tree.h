// Segtree:
//  > .apply(a, b, k)
//  > .get(a, b)
//  > .construct(init)
template<class Ix, class Data>
struct BinTree {
    /*
    BinTree<Ix, Data> *left;
    BinTree<Ix, Data> *right;

    Ix size;

    Data val;

    BinTree(Ix n, Data zero): size(n) {
        val = zero;

        if(size == 1) {
            left = nullptr;
            right = nullptr;
        } else {
            right = new BinTree<Ix, Data>((size + 1) / 2, zero);
            left = new BinTree<Ix, Data>(size / 2, zero);
        }
    }

    ~BinTree() {
        if(left != nullptr)
            delete left;
        if(right != nullptr)
            delete right;
    } 

    template<class F>
    void print(F f, int depth) {
        f(val, depth);
        if(size != 1) {
            left->print(f, depth + 1);
            right->print(f, depth + 1);
        }
    }
    */

    Ix size;
    Ix pos;

    vector<Data> *data;

    BinTree(Ix n, Data zero): size(n), pos {
        val = zero;

        if(size == 1) {
            left = nullptr;
            right = nullptr;
        } else {
            right = new BinTree<Ix, Data>((size + 1) / 2, zero);
            left = new BinTree<Ix, Data>(size / 2, zero);
        }
    }





    /*
    template<class F, class Pass>
    void recurse(F fun, Pass p) {
        auto left_fun = [&](Pass o) { left->recurse(fun, o) };
        auto right_fun = [&](Pass o) { right->recurse(fun, o) };

        fun();
    }
    */
};

template<class Ix, class Data, class Func, class A, class R, class C>
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
    public:
    struct Node {
        Func func;
        Data data;
    };
        BinTree<Ix, Node> *root;
        Data zero;
        Func id;

        A apply;
        R reduce;
        C compose;

    public:
        SegTree(Ix nsize, Data init, Data nzero, Func nid, A apply, R reduce, C compose): apply(apply), reduce(reduce), compose(compose) {
            zero = nzero;
            id = nid;

            root = new BinTree<Ix, Node>(nsize, Node {id, init});

            std::function<void(BinTree<Ix, Node>*)> fun = [&](BinTree<Ix, Node> *node) {
                if(node->size != 1) {
                    fun(node->left);
                    fun(node->right);
                    node->val.data = reduce(
                            apply(node->left->val.data, node->left->val.func),
                            apply(node->right->val.data, node->right->val.func));
                }
            };

            fun(root);

        }

        Data gt(Ix bg, Ix ed) {
            /*
            root->print([&] (Node n, int depth) {
                    for(int i = 0; i < depth; ++i) std::cout << "  ";
                    std::cout << n.data << " : " << n.func << std::endl;
                    },0);
                    */
            std::function<Data(Ix, Ix, BinTree<Ix, Node>*)> fun = [&](Ix b, Ix e, BinTree<Ix, Node> *node) {
                if(b <= 0 && e >= node->size) {
                    return apply(node->val.data, node->val.func);
                } else if(e <= 0 || b >= node->size) {
                    return zero;
                } else {
                    // Else branch never happens if node->size == 1; so nullptr's don't get derreferenced

                    return apply(reduce(
                                fun(b, e, node->left),
                                fun(b - node->left->size, e - node->left->size, node->right)),
                            node->val.func);
                }
            };

            return fun(bg, ed, root);
        }

        void st(Ix bg, Ix ed, Func f) {
            std::function<void(Ix, Ix, BinTree<Ix, Node>*)> fun = [&](Ix b, Ix e, BinTree<Ix, Node> *node) {
                if(b <= 0 && e >= node->size) {
                    node->val.func = compose(node->val.func, f);
                } else if(e <= 0 || b >= node->size) {
                } else {
                    // Else branch never happens if node->size == 1; so nullptr's don't get derreferenced
                    node->left->val.func = compose(node->left->val.func, node->val.func);
                    node->right->val.func = compose(node->right->val.func, node->val.func);
                    node->val.func = id;

                    fun(b, e, node->left);
                    fun(b - node->left->size, e - node->left->size, node->right);

                    node->val.data = reduce(
                            apply(node->left->val.data, node->left->val.func),
                            apply(node->right->val.data, node->right->val.func));
                }
            };

            fun(bg, ed, root);
        }

        ~SegTree() {
            delete root;
        }
};
