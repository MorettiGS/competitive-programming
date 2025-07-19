long long MRS(const vector<int>& as)
{
    auto N = as.size() - 1;
    vector<long long> ps(N + 1, 0);
    // O código assume que os índices da sequência as começam em 1
    for (size_t i = 1; i <= N; ++i)
        ps[i] = ps[i - 1] + as[i];

    long long ans = -oo;
    for (size_t i = 1; i <= N; ++i)
        for (size_t j = i; j <= N; ++j)
            ans = max(ans, ps[j] - ps[i - 1]);

    return ans;
}