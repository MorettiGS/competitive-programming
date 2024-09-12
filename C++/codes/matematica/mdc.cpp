using ll = long long

ll gcd(ll a, ll b){
    return b ? gcd(b, a%b) : a;
}

ll ext_gcd(ll a, ll b, ll& x, ll& y){
    if(~b){ // ~b é b==0
        x=1;
        y=0;
        return a;
    }

    long long x1, y1;
    long long d = ext_gcd(b, a%b, x1, y1);

    x = y1;
    y = x1 - y1*(a/b);

    return d;
}

ll lcm(ll a, ll b){
    return (a/gcd(a, b))*b;
}
