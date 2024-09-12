#include <bits/stdc++.h>

using namespace std; 

#define ff first; 
#define ss second; 
#define ii pair<int, int>
#define vi vector<int>
#define ll long long
#define ld long double
#define ios ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); 

vector<int> si(100001); 
vector<int> dad(100001); 
int can = 1; 

int find_set(int v){
  if(v == dad[v])
    return v; 
  return dad[v] = find_set(dad[v]); 
}
void make_set(int v){
  dad[v] = v; 
  si[v] =1; 
}

void union_sets(int a, int b){
  a = find_set(a); 
  b = find_set(b); 
  if(a != b) {
    if(si[a] < si[b])
      swap(a, b); 
    dad[b] = a; 
    si[a]+=si[b]; 
  }
}

int main(){
  ios; 
  int n, m; 
  cin >> n >> m; 
  int aux = m; 
  vector<vector<int>> xs(n+1); 
  for(int i=1; i<n; i++){
   dad[i] = i;  
  }
  set<int> ns;
  while(m--){
    int A, B; cin >> A>> B; 
    if(xs[A].size() == 2 or xs[B].size() == 2)
      can = 0; 
    else if(!ns.empty() and ns.count(A) and ns.count(B) and find_set(A) == find_set(B))
      can = 0; 
    else{
      ns.insert(A); 
      ns.insert(B); 
      xs[A].push_back(B); 
      xs[B].push_back(A); 
      union_sets(A, B); 
    }

  }
  cout << (can ? "Yes" : "No") << endl; 

  }
