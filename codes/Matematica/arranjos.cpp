#include <bits/stdc++.j>

#define ll long long;

ll A(ll n, ll p){
    if(n < p)
        return 0;

    ll res = 1;

    for(ll i = n; i > p; --i){
        res*=i;
    }

    return res;
}

//long long só aguenta 10!
//maior N! ou A^B

ll dp(int k, int a, int b){
    if(a < 0 || b < 0)
        return 0;
    
    if(k == 0)
        return 1;

    if(st[k][a][b] != -1)
        return st[k][a][b];

    auto res = dp(k-1, a-1, b) + dp(k-1, a, b-1);

    st[k][a][b] = res;
    return res;
}
