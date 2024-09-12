//(N ** fi de p) % p == 1 sempre
// sistema reduzido de resíduo é os diferentes restos que deixam (7 vai ter t=6) - pega todos os restos
// números coprimos - número que mdc entre eles é 1
// coprimos de 6 = 1,4,5 


// TEOREMA DE FERMAT
// a^p é congruente a a(mod p) - a é inteiro e p é primo
// 

// TEOREMA DE EULER
// a^fi de m é congruente a 1 mod m
// só de primo o fi é -1
// fatora em primo e sabe que é -1
// fi de qulquer valor é = fi de primo 1 * fi de primo 2

// Fatoracao em primos
#define ll long long

ll phi(){

}

ll fatp(int x){
    map<int, int> m;

    for(int i = 2; i * i < x; i++){
       while(x%i == 0){
        x/=i;
        m[i]++;
       }



    }


} 

// verificar se é primo
bool is_p(int n){
    if(n < 2)
        return false;

    if(n == 2)
        return true;

    if(n%2 == 0)
        return false;

    for(int i = 3; i * i <= n; i+=2){
        if(n%i == 0)
            return false;
    }
    return true;
}

// crivo
vector<long, long> primes(ll N){
    bitset<MAX> sieve;
    vector<long long> ps{2};
    sieve.set();

    for(ll i = 3; i<=N; i+=2){
        if(sieve[i]){
            ps.push_back(i);
            for(ll j = i * i; j<=N; j+=2*i){
                sieve[j] = false;
            }
        }
    }
    return ps;
}
