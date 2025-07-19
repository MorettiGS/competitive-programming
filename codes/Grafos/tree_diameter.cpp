pair<int, int> bfs(int s, int N) {
    vector<int> dist(N + 1, oo); dist[s] = 0;
    queue<int> q; q.push(s);
    int last = s;
    while (not q.empty()) {
        auto u = q.front(); q.pop();
        last = u;
        for (auto v : adj[u]) if (dist[v] == oo) { dist[v] = dist[u] + 1; q.push(v); }
    }
    return { last, dist[last] }; }

int diameter(int N) {
    auto [v, _] = bfs(1, N);
    auto [w, D] = bfs(v, N); return D; }
