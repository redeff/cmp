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
        vector<vector<bool>> graph(ns[i], vector<bool>(ns[i], false));
        for(int j = 0; j < ms[i]; ++j) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            graph[a][b] = true;
            graph[b][a] = true;
        }
        process(graph);
    }
}
