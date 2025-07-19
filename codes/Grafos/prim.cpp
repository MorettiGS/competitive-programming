int prim(int u, size_t N){
    set<int> C; C.emplace(u);
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    for (auto [v, w] : adj[u]) pq.emplace(w, v);
    int mst = 0;
    while (C.size() < N) {
        int v, w;
        do {
            tie(w, v) = pq.top(); pq.pop();
        } while (C.count(v));
        mst += w; C.emplace(v);
        for (auto [s, p] : adj[v]) pq.emplace(p, s);
    }
    return mst; }
