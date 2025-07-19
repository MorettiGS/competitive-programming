void precomp(int N, int M, const vector<int>& s) {
    for (int u = 1; u <= N; ++u) S[u][0] = s[u];
    for (int i = 1; i <= M; ++i)
        for (int u = 1; u <= N; ++u)
            S[u][i] = S[S[u][i - 1]][i - 1];
}

int succ(int u, int k) {
    for (int i = 0; (1 << i) <= k; ++i) if (k & (1 << i)) u = S[u][i];
    return u;
}
