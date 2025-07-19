int dist[MAX][MAX];
int st[MAX][1 << MAX];
int tsp(int i, int mask, int N) {
    if (mask == (1 << N) - 1) return dist[i][0];
    if (st[i][mask] != -1) return st[i][mask];
    int res = oo;
    for (int j = 0; j < N; ++j) {
        if (mask & (1 << j)) continue;

        res = min(res, tsp(j, mask | (1 << j), N) + dist[i][j]);
    }
    return (st[i][mask] = res);
}