#include <bits/stdc++.h>

using namespace std; 

#define ff first; 
#define ss second; 
#define ii pair<int, int>
#define vi vector<int>
#define ll long long
#define ld long double
#define ios ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); 
const int MAXN = (1e5*3)+1;
vector<int> t[4*MAXN];

void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = vector<int>(1, a[tl]);
    } else { 
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        merge(t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(),
              back_inserter(t[v]));
    }
}


int query(int v, int tl, int tr, int l, int r, int x) {
    if (l > r)
        return 0;
    if (l == tl && r == tr) {
      // QTD DE NUMEROS MAIORES OU IGUAIS A X 
        vector<int>::iterator pos = lower_bound(t[v].begin(), t[v].end(), x);
        if (pos != t[v].end()){
            return t[v].end()-pos;
        }
        return 0;
    }
    int tm = (tl + tr) / 2;
    //se quiser so o lower bound do intervalo, tem que ser o min das querys
    return (query(v*2, tl, tm, l, min(r, tm), x) + query(v*2+1, tm+1, tr, max(l, tm+1), r, x));
}

int main(){
    ios; 
    int N, M; 
    cin >> N >> M; 
    int adj[N];  
    for(int i=0; i<N; i++){
        cin >> adj[i]; 
    }

    build(adj, 1, 0, N-1); 
    while(M--){
        int x, y, z; 
        cin >> x >> y >> z; 
        int res = 0; 
        if(adj[x-1] >= y){
            res = 0;   
        } 
        else{
            res = query(1, 0, N-1, x-1, x+z-1, y); 
        }
        cout << res << endl;

    }
    return 0; 

}
