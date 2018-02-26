struct Info {
    int color;
    int nxt;
    int prv;
    int index;
    // int jmp;

    int col_nxt;
    int col_prv;
};

struct Range {
    int b;
    int e;
}

struct ColorInfo {
    Range extremes;
    bool mixed;
    bool tomix;
};

struct Problem {
    vector<Info> v;
    // vector<Range> extremes;

    vector<ColorInfo> colors;

    void doit(int start) {
        int n = 1;
        for(i = v[start].nxt; i != start; ++i) {
            n++;
        }
        auto dist = [&](Range r) {
            if(v[r.b].index < v[r.e].index) return v[r.e].index - v[r.b].index;
            return n - (v[r.b].index - v[r.e].index);
        };

        for(int i = start, bool begun = true; i != start || begun; i = v[i].nxt, begun = false) {
            colors[v[i].color].tomix = false;
            colors[v[i].color].mixed = false;

            if(v[i].prv > i) {
                Range max_interval;
                max_interval.b = i;
                max_interval.e = v[i].col_nxt;
                for(int j = v[i].col_nxt; j != 0; j = v[j].col_nxt) {
                    Range new_interval;
                    new_interval.b = j;
                    new_interval.b = v[j].col_nxt;

                    if(dist(new_interval) > dist(max_interval)) {
                        max_interval = new_interval;
                    }
                }

                // No queremos el hueco mas grande sino lo opuesto
                colors[v[i].color].extremes.b = max_interval.e;
                colors[v[i].color].extremes.e = max_interval.b;
            }
        }

        int init = s;
        vector<int> sts;
        do {
            vector<int> connected = v[init].color;

            int right = init;
            int left = init;
            
            Range bounds = colors[v[init].color].extremes;

            while(v[bounds.e].nxt != bounds.b) {
                bool blocked = true;
                if(bounds.contains(v[right].nxt)) {
                    right = v[right].nxt;
                    blocked = false;
                }

                if(bounds.contains(v[left].prv)) {
                    left = v[left].prv;
                    blocked = false;
                }

                if(blocked) break;

                auto add_bound = [&](Range new_bound) {
                    // TODO: check
                    if(bounds.contains(new_bounds.b) && bounds.contains(new_bounds.e)) return;
                    if(new_bounds.contains(bounds.b) && new_bounds.contains(bounds.e)) {
                        connected = {v[new_bounds.b].color};
                        return;
                    }
                    else connected.push_back(v[new_bounds.b].color);
                    if(new_bounds.contains(bounds.b)) {
                        bounds.b = new_bounds.b;
                    }

                    if(new_bounds.contains(bounds.e)) {
                        bounds.e = new_bounds.e;
                    }
                };

                auto recurse_big_enough = [&]() {
                    for(auto c : connected) {
                        mixed[c] = true;
                    }

                    int example = connected.back();
                    int i = colors[example].extremes.b;
                    int last_mixed = i;
                    vector<int> starts;
                    starts.push_back(i);
                    int prv = i;
                    i = v[i].nxt;
                    for(;i != colors[example].extremes.b; i = v[i].nxt) {
                        if(colors[v[i].color].mixed) {
                            v[v[i].prv].nxt = last_mixed;
                            v[last_mixed].prv = v[i].prv;
                            last_mixed = i;
                            starts.push_back(i);
                            v[i].color = example;
                        } else {
                            if(v[i])    
                        }
                        prv = i;
                    }

                    for(auto s : starts) {
                        int last_tomix = s;
                        for(int i = v[s].nxt; i != s; i = v[i].nxt) {
                            if(v[i].color == example) {
                                v[i].color_prv = last_tomix;
                                v[last_tomix].color_nxt = i;
                                last_tomix = i;
                            }
                        }

                        v[s].color_prv = last_tomix;
                        v[last_tomix].color_nxt = s;
                    }

                    v[prv].nxt = last_mixed;
                    v[last_mixed].prv = prv;

                    for(auto s : starts) {
                        doit(s);
                    }
                };


                add_bound(colors[v[left].color].extremes);
                if(dist(bounds) >= n/2) {
                    recurse_big_enough();
                    return;
                }

                add_bound(colors[v[right].color].extremes);
                if(dist(bounds) >= n/2) {
                    recurse_big_enough();
                    return;
                }
            }
            sts.push_back(bounds.b);

        } while (v[bounds.e].nxt != bounds.b);
    }
};
