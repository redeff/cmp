template<class Ix, class Data>
class VersionGraph {
    bool leaf;
    bool has_data;

    VersionGraph *prv;
    VersionGraph *nxt;

    vector<VersionGraph*> *conn;
    vector<vector<Data>*> *ns;

    VersionGraph(Ix n, Data init) {
        leaf = true;
        has_data = true;
        prv = nullptr;
        nxt = nullptr;
        conn = nullptr;
        ns = new vector<Data>(n, init); 
    }

    VersionGraph modify() {

    }
}

class Array {
    
}
