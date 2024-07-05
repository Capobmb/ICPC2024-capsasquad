#include<bits/stdc++.h>
using namespace std;
using ll=long long;

void solve(){
  ll N; cin>>N;
  if(!N){exit(0);}

  vector<ll> A(N);
  for(auto &i:A) {cin>>i;}

  ll c=0;
  for(ll i=0;i<N;i++){
    if(c+A[i]>300){continue;}
    c+=A[i];
  }

  cout<<c<<"\n";

}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  while(true){ solve(); }
}
