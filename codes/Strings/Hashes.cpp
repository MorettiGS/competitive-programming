int f(char c) { return c - 'a' + 1; }

/* Hash simples */
int h(const string& s)
{
    int N = s.size();
    long long ans = 0, p = 31, q = 1'000'000'007;

    for (int i = N - 1; i >= 0; --i){
        ans = (ans * p) % q;
        ans = (ans + f(s[i])) % q;
    }
    return ans;
}

/* Hash duplo */
int hi(long long pi, long long qi, const string& s)
{
    int N = s.size();
    long long ans = 0;
    for (int i = N - 1; i >= 0; --i) {
        ans = (ans * pi) % qi;
        ans = (ans + f(s[i])) % qi;
    }
    return ans;
}

pair<int, int> h(const string& s)
{
    constexpr long long p1 = 31, q1 = 1'000'000'007;
    constexpr long long p2 = 29, q2 = 1'000'000'009;

    return { hi(p1, q1, s), hi(p2, q2, s) };
}

int main()
{
    string s;
    cin >> s;

    auto [h1, h2] = h(s);

    cout << "(" << h1 << ", " << h2 << ")\n";

    return 0;
}

/* Contagem de substrings distintas */
constexpr ll p = 31, q = 1'000'000'007;

int h(const string& s)
{
    int N = s.size();
    ll ans = 0;

    for (int i = N - 1; i >= 0; --i) {
        ans = (ans * p) % q;
        ans = (ans + f(s[i])) % q;
    }

    return ans;
}

vector<ll> prefixes(const string& s)
{
    int N = s.size();
    vector<ll> ps(N, 0);

    for (int i = 0; i < N; ++i)
        ps[i] = h(s.substr(0, i + 1));

    return ps;
}

ll fast_exp_mod(ll a, ll n)
{
    ll res = 1, base = a;

    while (n)
    {
        if (n & 1)
            res = (res * base) % q;

        base = (base * base) % q;
        n >>= 1;
    }

    return res;
} 

vector<ll> inverses(ll N)
{
    vector<ll> is(N);
    ll base = 1;

    for (int i = 0; i < N; ++i) {
        is[i] = fast_exp_mod(base, q - 2);
        base = (base * p) % q;
    }

    return is;
}

int h(int i, int j, const vector<ll>& ps, const vector<ll>& is)
{
    auto diff = i ? ps[j] - ps[i - 1] : ps[j];
    diff = (diff * is[i]) % q;
    return (diff + q) % q;
}

int unique_substrings(const string& s)
{
    int N = s.size();
    set<ll> hs;
    auto ps = prefixes(s);
    auto is = inverses(s.size());

    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            auto hij = h(i, j, ps, is);
            hs.insert(hij);
        }
    }

    return hs.size();
}
