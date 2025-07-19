int A[MAX][MAX], S[MAX][MAX];
int MSS(int N, int M) {
    for (int i = 0; i < N; ++i)
        S[i][0] = A[i][0];
    for (int j = 0; j < M; ++j)
        S[0][j] = A[0][j];

    int ans = 0;
    for (int i = 1; i < N; ++i)
        for (int j = 1; j < M; ++j) {
            S[i][j] = A[i][j] == 0 ? 0 : min({ S[i-1][j], S[i][j-1], S[i-1][j-1] }) + 1;

            ans = max(ans, S[i][j]);
        }
    return ans;
}