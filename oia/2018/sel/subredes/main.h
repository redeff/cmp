void parse() {
    {   // ignore subgraph
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            string s;
            cin >> s;
        }
    };
    
    int k;
    cin >> k;
    vector<int> ns(k);
    vector<int> ms(k);
    for(int i = 0; i < k; ++i) {
        cin >> ns[i] >> ms[i];
    }

    for(int i = 0; i < k; ++i) {
        vector<unordered_set<int>> graph(ns[i]);
        for(int j = 0; j < ms[i]; ++j) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            graph[a].insert(b);
            graph[b].insert(a);
        }
        process(graph);
    }
}