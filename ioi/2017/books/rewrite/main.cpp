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

void doit(Node *start) {
    int n = start->prv -> index - start->index;

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
