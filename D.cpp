#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct Namori {
  ll path_len;
  vector<ll> path, loop;
  Namori(const vector<ll> &g, ll s = 0) {
    vector<ll> vis(g.size(), -1);
    for(ll i = 0, p = s;; i++, p = g[p]) {
      if(vis[p] != -1) {
        path_len = vis[p];
        break;
      }
      loop.emplace_back(p);
      vis[p] = i;
    }
    for(ll i = 0; i < path_len; i++) { path.emplace_back(loop[i]); }
    loop.erase(loop.begin(), loop.begin() + path_len);
  }
  inline ll operator()(ll k) const { return k < path_len ? path[k] : loop[(k - path_len) % loop.size()]; }
};

constexpr int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

void solve(){

  ll N;
  cin>>N;

  if(!N){exit(0);}

  ll A,B,D;
  cin>>A>>B>>D;

  vector<vector<ll>> s(101,vector<ll>(101,0));
  for(ll i=0;i<N;i++){
    ll x,y;
    cin>>x>>y;
    s[x][y]=1;
  }

  vector<ll> nx(101*101*4,-1),vis(101*101*4,-1);

  auto id=[&](ll i,ll j,ll d){return i*404+j*4+d;};

  queue<tuple<ll,ll,ll>> q;
  q.emplace(A,B,0);

  ll c=0;
  ll lx,ly,ld=-1;
  while(!q.empty()){
    auto [x,y,d]=q.front();
    // cout<<x<<" "<<y<<" "<<d<<"\n";
    vis[id(x,y,d)]=c++;
    q.pop();

    for(ll i=d;;i++){
      ll j=i%4;
      ll ni=x+dx[i%4],nj=y+dy[i%4];
      if(ni<0||ni>100||nj<0||nj>100) {
        lx=ni,ly=nj,ld=j;
        while(!q.empty()){q.pop();}
        break;
      }
      if(!s[ni][nj]){
        nx[id(x,y,d)]=id(ni,nj,j);
        if(vis[id(ni,nj,j)]!=-1){
          // cout<<"ad\n";
          while(!q.empty()){q.pop();}
          break;
        }
        else{
          q.emplace(ni,nj,j);
          break;
        }
      }
    }
  }

  if(ld!=-1){
    if(D-c>=0) {
      // cout<<ld<<" ";
      cout<<lx+dx[ld]*(D-c)<<" "<<ly+dy[ld]*(D-c)<<"\n";
    }
    else{
      // cout<<"A ";
      for(ll i=0;i<101*101*4;i++){
        if(vis[i]==D){
          ll j=i/4;
          cout<<j/101<<" "<<j%101<<"\n";
        }
      }
    }
  }
  else{
    Namori G(nx,id(A,B,0));
    ll ans=G(D)/4;
    // cout<<"s"<< "   ";
    cout<<ans/101<<" "<<ans%101<<"\n";
  }

}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  while(true){ solve(); }
}
