#define ll long long

ll number_of_divisors(int n, const vector<int>& primes){
    auto fs = factorization(n, primes);
    ll res = 1;

    for(auto [p, k] : fs)
        res*=(k+1);
    
    return res;
}

ll sum_of_divisors(int n, const vector<int>& primes){
    auto fs = factorization(n, primes);
    ll res = 1;
    
    for(auto [p, k] : fs){
        ll pk = p;

        while(k--){
            pk *= p;
        }

        res *= (pk-1)/(p-1);
    }
    return res;
}

int phi(int n, const vector<int>& primes){
    if(n==1)
        return 1;
    
    auto fs = factorization(n, primes);
    auto res = n;

    for( auto [p, k] : fs){
        res /= p;
        res *= (p-1);
    }
    return res;
}



