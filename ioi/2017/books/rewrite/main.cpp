struct Node {
    Node *nxt;
    Node *prv;

    Node *nxt_cyc;
    Node *prv_cyc;

    int index;
}

struct Range {
    Node* b;
    Node* e;

    Range(Node* b, Node* e): b(b), e(e) {}
    Range() {}

    bool contains(Node* i) {
        if(b->index < e->index) return b->index <= i->index && i->index <= e->index;
        else return i->index <= e->index || b->index <= i->index;
    }
}

void set_cyc(Node* a, Node* b) {
    a->nxt_cyc = b;
    b->prv_cyc = a;
}

void fuse(Node *a, Node *b) {
    Range as(a, a->nxt_cyc);

    Node* bs[4];
    bs[0] = b;
    for(int i = 1; i < 4; ++i) {
        bs[i] = bs[i - 1]->nxt_cyc;
    }

    for(int i = 0; i < 4; ++i) {
        if(bs[i] == as.b || bs[i] == as.e) return;
    }

    for(int i = 1; i < 4; ++i) {
        if(as.contains(bs[i - 1]) != as.contains(bs[i])) return;
    }

    for(int i = 1; i < 4; ++i) {
        if(as.contains(bs[i]) != Range(bs[i - 1], bs[i]).contains(a.b)) {
            /*
            as.b->nxt_cyc = bs[i];
            bs[i]->prv_cyc = as.b;
            */
            set_cyc(as.b, bs[i]);

            /*
            as.e->prv_cyc = bs[i - 1];
            bs[i - 1]->nxt_cyc = as.e;
            */
            set_cyc(bs[i - 1], as.e);

            return;
        }
    }

    // Don't ask
    set_cyc(bs[0], bs[2]);
    set_cyc(bs[2], as.e);

    set_cyc(as.b, bs[1]);
    set_cyc(bs[1], bs[3]);
}

void doit(Node *start) {
    int n = start->prv->index - start->index;

    auto len = [&](Range r) {
        int ix_b = r.b->index;
        int ix_e = r.e->index;
        if(ix_b < ix_e) return ix_e - ix_b;
        else return n - (ix_b - ix_e);
    }

    Range big(start, start->nxt_cyc->prv), sml(start->next_cyc, start->prv);
    if(dist(big) < dist(sml)) {
        Range tmp = big;
        big = sml;
        sml = tmp;
    }

    vector<Node*> big_cyc;
    vector<Node*> sml_cyc;

    for(Node* i = sml.b; i != sml.e->nxt; i = i->nxt) {
        if(big.contains(i->prv_cyc)) {
            big_cyc.push_back(i->prv_cyc);
            sml_cyc.push_back(i);

            Node* go_back = i;
            while(sml.contains(go_back->nxt_cyc)) go_back = go_back->nxt_cyc;

            set_cyc(i->prv_cyc, go_back->nxt_cyc);
            /*
            i->prv_cyc->nxt_cyc = go_back->nxt_cyc;
            go_back->nxt_cyc->prv_cyc = i->prv_cyc;
            */

            set_cyc(go_back, i);
            /*
            i->prv_cyc = go_back;
            go_back->nxt_cyc = i;
            */
        }
    }

    for(int i = 1; i < big_cyc.size(); ++i) {
        fuse(big_cyc[i - 1], big_cyc[i]);
    }

    for(int i = 1; i < sml_cyc.size(); ++i) {
        fuse(sml_cyc[i - 1], sml_cyc[i]);
    }

    big.e->nxt = big.b;
    big.b->prv = big.e;

    sml.e->nxt = sml.b;
    sml.b->prv = sml.e;

    doit(sml.b);
    doit(big.b);

    
    big.e->nxt = sml.b;
    big.b->prv = sml.e;

    sml.e->nxt = big.b;
    sml.b->prv = big.e;

    Node* nxt_big = big.b->nxt_cyc;
    Node* nxt_sml = sml.b->nxt_cyc;

    set_cyc(big.b, nxt_sml);
    set_cyc(sml.b, nxt_big);

    /*

    vector<Node*> come;
    vector<Node*> go;

    for(Node* i = sml.b; i != sml.e->nxt; i = i->nxt) {
        if(big.contains(i->prv)) come.push_back(i);
        if(big.contains(i->nxt)) go.push_back(i);
    }

    assert(come.size() == go.size());

    while(!come.empty()) {
        Node* c = come.back();
        Node* g = go.back();
        come.pop_back();
        go.pop_back();

        c->prv->nxt = g->nxt;
        g->nxt->prv = c->prv;
        c->nxt = g;
        g->prv = c;
    }

    doit(sml.b);
    doit(big.b);
    */

    /*
    auto len = [&](Range r) {

        int ix_b = r.b->index;
        int ix_e = r.e->index;
        if(ix_b < ix_e) return ix_e - ix_b;
        else return n - (ix_b - ix_e);
    }

    int color = start->color;

    vector<pair<Range, Range>> active;
    while(!active.empty()) {
        Range r = active.back();
    }
    */
    /*
    Range inactive;

    {
        Range a(start, start->color_nxt), b(start->color_prv, start);
        if(dist(a) < dist(b)) active.push_back(a);
        else active.push_back(b);
    }
    inactive.emplace_back(start->color_nxt->nxt, start->prv);

    vector<Range> independent;

    while(!active.empty()) {
        Range r = active.back();
        active.pop_back();


        for(i = r.b; i != r.e->nxt; i = i->nxt) {
            if(!r.contains(i->color_nxt)) {
                if(r.b != i->prv) active.emplace_back(r.b, i->prv);
                if(r.e != i->nxt) active.emplace_back(i->nxt, r.e);

                i->color = color;

                if(inactive.contains(i->color_nxt)) {
                    Range a(inactive.b, i->color_nxt), b(i->color_nxt, inactive.e);
                    if(dist(a) < dist(b)) {
                        inactive = b;
                        inactive.b = inactive.b->nxt;
                        active.push_back(a);
                    } else {
                        inactive = a;
                        inactive.e = inactive.e->nxt;
                        active.push_back(b);
                    }
                }

                goto end;
            }
        }

        independent.push_back(r);

end:
        ;
    }

    for(Range r : indenpendent) {
        r.b->prv = r.e;        
        r.e->prv = r.b;        
        doit(r.b);
    }
    */
}
