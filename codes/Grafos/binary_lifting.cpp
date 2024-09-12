#include <bits/stdc++.h> 
 
using namespace std; 
// O problema deu 109 o k entao log2 10e9 e 30; 
const int MAXLOG2 = 30; 
const int MAXN = 2e5+10; 
vector<vector<int>> pre(MAXLOG2+1, vector<int>(MAXN)); 
 
 // Pre processa os pais em expoentes de 2, [0] significa 2e0
void pre_processamento(vector<int> sucessores, int n){
  for(int i=1;i<=n; i++){
    pre[0][i] = sucessores[i]; 
  }
 
  for(int p=1; p<=MAXLOG2; p++){
    for(int i=1; i<= n; i++){
      if(pre[p-1][i] == -1){
        pre[p][i] = -1; 
      }
      else{
        pre[p][i] = pre[p-1][pre[p-1][i]]; 
      }
      }
 
  }
}
 //kesimo pai do no 
int kth_succ(int n, int k){
  int aux = n; 
  for(int i=0; i<=MAXLOG2; i++){
    if(k & (1 << i)){
      aux = pre[i][aux]; 
      if(aux == -1)
        return -1;  
    }
  }
  return aux; 
}
 
int main(){
  int n, q; cin >> n >> q; 
  vector<int> sucessores(n+1); 
  sucessores[1] = -1; 
  sucessores[0] = -1; 
  for(int i=2;i<= n; i++){
   int x; cin >> x; 
   sucessores[i] = x; 
  } 
 
  pre_processamento(sucessores, n); 
 
  while(q--){
    int a, b; 
    cin >> a >> b; 
    cout << kth_succ(a, b) << endl; 
  }
}