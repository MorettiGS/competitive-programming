#include <bits/stdc++.h>
#include <vector>
#define ll long long

template<typename T>
ll permutations(const vector<T>& A){
    map<T, int>hist;

    for(auto a: A)
        ++hist[a];
    
    ll res = factorial(A.size());

    for(auto [a, ni]: hist)
        res/= factorial(ni);
    
    return res;
}

int main(){
    vector<int> A {5, 3, 4, 1, 2};

    sort(A.begin(), A.end());

    do{
        for(size_t i = 0; i<A.size(); ++i){
            cout << A[i] << (i+1 == A.size() ? '\n' : ' ');
        }
    } while (next_permutations(A.begin(), A.end()));
    return 0;
}
