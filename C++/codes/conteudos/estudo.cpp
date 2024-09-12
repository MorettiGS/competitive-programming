#include<bits/stdc++.h>
#include <cstddef>
#include <ios>

using namespace std;

using ll = long long;

ll fp(ll a, ll b){

  if ( not b)
    return 1;

  ll pr = fp(a, b/2);
  
  return ~b & 1 ? pr * pr : pr * pr * a;

}


ll ph(ll x){

  if ( x == 1)
    return 1;

  map<int, int> m;

  for ( int i = 2; i * i <= x; i++)
    while ( x % i == 0){
      x/=i;
      m[i]++;
  }

  if (x and x != 1)
    m[x]++;


  ll res = 1;
  for ( auto [primo, potencia ] : m)
    res *= (primo - 1) * fp(primo, potencia - 1);

  return res;

}




int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cout << ph(400) << endl;



}
