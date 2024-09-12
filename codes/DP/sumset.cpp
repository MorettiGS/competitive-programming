#include <bits/stdc++.h> 

using namespace std;
int MAXN = 1e5+1; 
int MAXM = 1e3+1; 
vector<vector<int>> dp(MAXM, vector<int> (MAXN, -1)); 
vector<int> xs; 
int response = 0; 

int solve(int n, int valor){
  if(n == -1 and valor == 0 ){ 
    response = 1;
     return 1; 
  }
 if(n == -1 or valor < 0){
    return 0; 
  }

 auto &rep = dp[n][valor]; 
 if(rep != -1){
   return rep; 
  }
  
 rep = solve(n-1, valor) || solve(n-1, valor-xs[n]); 
return rep; 

}

int main(){
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  int V, N; 
  cin >> V >> N; 
  xs = vector<int>(N); 
  for(auto &i: xs)
    cin >> i; 
  solve(N-1, V); 
  // se for possivel formar o valor v com o array
  cout << (response ? "S" : "N") << endl; 

}
