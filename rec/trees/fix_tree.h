
template<class Ix>
auto lsb(Ix i) -> decltype(i) {
    return i & (-i);
}

template<class Data, class Ix>
struct FixTree {
    Ix n;
    Ix root;
    vector<Data> ns;

    FixTree(Ix size): n(size), ns(n) {
        root = 0;
        while(root < n) {
            root = 2 * root + 1;
        }
        root = (root - 1) / 2;
    }

    FixTree(Ix size, Data zero): n(size), ns(n, zero) {
        root = 0;
        while(root < n) {
            root = 2 * root + 1;
        }
        root = (root - 1) / 2;
    }


    Data ge(Ix i) {
        return ns[i];
    }

    void se(Ix i, Data val) {
        ns[i] = val;
    }

    std::optional<Ix> right(Ix ix) {
        if(ix % 2 == 0) return {};
        int child = ix + (lsb(ix + 1) >> 1);
        if(child < n) return child; else return {};
    }

    std::optional<Ix> left(Ix ix) {
        if(ix % 2 == 0) return {};
        return ix - (lsb(ix + 1) >> 1);
    }

    std::optional<Ix> parent(Ix ix) {
        Ix delta = lsb(ix + 1);
        if((ix + 1) & delta) return ix - delta;
        else if(ix + delta < n) return ix + delta;
        else return {};
    }

    template<class F>
    void hi_bound(Ix ix, F f) {
        Ix node = root;
        while(true) {
            if(node < ix) {
                
            }
        }
    }
};

template<class Ix, class Data, class F>
auto rec_create(Ix n, F f) -> FixTree<Data, Ix> {
    vector<bool> visited(n, false);
    auto fx = FixTree<Ix, Data>(n);
    
    std::function<void(int)> solve = [&](Ix i) -> Data {
        if(fx.right(i).has_value()) {
            solve(*fx.right(i));
        }

        if(fx.left(i).has_value()) {
            solve(*fx.left(i));
        }

        f(i, &fx);
    }

    solve(fx.root);
}