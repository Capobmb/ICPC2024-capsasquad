#include<bits/stdc++.h>
using namespace std;
using ll=long long;

template<typename S, auto op> struct Doubling {
  static_assert(is_convertible_v<decltype(op), function<S(S, S)>>);

 private:
  int n = 0;
  vector<vector<ll>> nxts;
  vector<vector<S>> prds;

  void build() {
    vector<ll> nxt(n);
    vector<S> prd(n);
    for(int i = 0; i < n; i++) {
      if(int j = nxts.back()[i]; in(j)) {
        nxt[i] = nxts.back()[j];
        prd[i] = op(prds.back()[i], prds.back()[j]);
      }
      else {
        nxt[i] = j;
        prd[i] = prds.back()[i];
      }
    }
    nxts.emplace_back(move(nxt));
    prds.emplace_back(move(prd));
  }
  inline bool in(int i) const noexcept { return 0 <= i && i < n; }
  int pow_next(int s, int d) {
    assert(in(s));
    while(ssize(nxts) <= d) { build(); }
    return nxts[d][s];
  }
  const S &pow_prod(int s, int d) {
    assert(in(s));
    while(ssize(nxts) <= d) { build(); }
    return prds[d][s];
  }

 public:
  Doubling() = default;
  Doubling(const vector<ll> &g, vector<S> &w): n(ssize(g)), nxts(1, g), prds(1, w) { assert(ssize(g) == ssize(w)); }
  int next(int s, ll k) {
    for(int d = 0; k > 0 && in(s); d++, k >>= 1) {
      if(k & 1) { s = pow_next(s, d); }
    }
    return s;
  }
  S prod(int s, ll len) {
    assert(in(s));
    assert(len > 0);
    int d = 0;
    while(!(len & 1)) {
      d++;
      len /= 2;
    }
    S r = pow_prod(s, d);
    s = pow_next(s, d);
    for(++d, len /= 2; len && in(s); d++, len /= 2) {
      if(len & 1) {
        r = op(r, pow_prod(s, d));
        s = pow_next(s, d);
      }
    }
    return r;
  }
  int distance(int s, int l, int r) {
    assert(in(s));
    if(s <= l || r <= s) { return 0; }
    int d = 0;
    while(l < pow_next(s, d) && pow_next(s, d) < r) {
      if((1 << d) >= n) { return -1; }
      d++;
    }
    int ret = 0, cur = s;
    for(--d; d >= 0; d--) {
      if(int nxt = pow_next(cur, d); l < nxt && nxt < r) {
        ret += 1 << d;
        cur = nxt;
      }
    }
    return ret + 1;
  }
  template<typename F> ll maxlen(const int s, F f, const int maxd = 60) {
    assert(in(s));
    int d = 0;
    while(d <= maxd && f(pow_prod(s, d))) {
      if(!in(pow_next(s, d))) { return 1LL << maxd; }
      d++;
    }
    if(d > maxd) { return 1LL << maxd; }
    d--;
    int cur = pow_next(s, d);
    ll len = 1LL << d;
    S p = pow_prod(s, d);
    for(int e = d - 1; e >= 0; e--) {
      if(S nxtp = op(p, pow_prod(cur, e)); f(nxtp)) {
        swap(p, nxtp);
        cur = pow_next(cur, e);
        len += 1LL << e;
      }
    }
    return len;
  }
};
// https://hitonanode.github.io/cplib-cpp/other_algorithms/binary_lifting.hpp

using S = ll;
S op(S l, S r) { return ; }

constexpr int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1}, dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void solve(){
  ll A,B,X,Y,N;
  cin>>A>>B>>X>>Y>>N;

  if(!A){exit(0);}
  vector<ll> x(N),y(N);
  for(ll i=0;i<N;i++){cin>>x[i]>>y[i];}

  set<pair<ll,ll> > st;
  for(ll i=0;i<N;i++){st.insert({x[i],y[i]});}

  auto id=[&](ll type,ll i,ll dir){
    ll r=0;
    if(type>=1){r+=A+1;}
    if(type>=2){r+=B+1;}
    if(type>=3){r+=A+1;}
    return r*2+dir;
  };

  auto inv=[&](ll idx)->tuple<ll,ll,ll>{
    ll dir=idx%2;
    idx>>=1;
    if(idx<=A){return {0,idx,dir};}
    idx-=A+1;
    if(idx<=B){return {1,idx,dir};}
    idx-=B+1;
    if(idx<=A){return {2,idx,dir};}
    idx-=A+1;
    return {3,idx,dir};
  };

  vector<ll> v((A+1)*(B+1),-1);
  for(ll i=0;i<=A;i++){
    if(i<B){v[id(0,i,0)]=id(3,i,1);}
    if(i>B){v[id(0,i,0)]=id(2,i-B,0);}
    if(i+B<A){v[id(0,i,1)]=id(2,i+B,1);}
    if(i+B>A){v[id(0,i,1)]=id(1,A-i,1);}
  }
  for(ll i=0;i<=B;i++){
    if(B-i<A){v[id(1,i,1)]=id(2,A-B+i,0);}
    if(B-i>A){v[id(1,i,1)]=id(3,i+A,1);}
    if(i<A){v[id(1,i,0)]=id(0,A-i,0);}
    if(i>A){v[id(1,i,0)]=id(3,i-A,0);}
  }
  for(ll i=0;i<=A;i++){
    if(i>B){v[id(2,i,0)]=id(0,i-B,0);}
    if(i<B){v[id(2,i,0)]=id(3,A-i,0);}
    if(A-i>B){v[id(2,i,1)]=id(0,i+B,1);}
    if(A-i<B){v[id(2,i,1)]=id(1,B-A+i,0);}
  }
  for(ll i=0;i<=B;i++){
    if(i>A){v[id(3,i,0)]=id(1,i-A,0);}
    if(i<A){v[id(3,i,0)]=id(0,i,1);}
    if(B-i>A){v[id(3,i,1)]=id(1,i+A,1);}
    if(B-i<A){v[id(3,i,1)]=id(2,B-i,1);}
  }

  vector<vector<ll>> ng((A+1)*(B+1));
  ll n=(A+1)*(B+1);
  for(ll i=0;i<N;i++){
    ll s=x[i]+y[i],d=x[i]-y[i];
    if(s<=A){v[id(0,s,1)]=n;}
    else{v[id(1,s-A,1)]=n;}
    if(s<=B){v[id(3,s,0)]=n;}
    else{v[id(2,s-B,0)]=n;}
    if(d+A<=B){v[id(1,d+A,0)]=n;}
    else{v[id(2,B-d,0)]=n;}
    if(d>=0){v[id(3,d,1)]=n;}
    else{v[id(0,-d,1)]=n;}
  }

  ll s=X+Y,d=X-Y;
  for(ll i=1;i<8;i+=2){
    ll xx=X,yy=Y;
    while(true){
      xx+=dx[i];
      yy+=dy[i];
      if(s.count({xx,yy})){break;}
      if(xx<0||xx>A||yy<0||yy>B) {
        if(i==1){
          if(d+A<=B){v[id(1,d+A,0)]=n+1;}
          else{v[id(2,B-d,0)]=n+1;}
        }
        if(i==3){
          if(s<=B){v[id(3,s,0)]=n+1;}
          else{v[id(2,s-B,0)]=n+1;}
        }
        if(i==5){
          if(d>=0){v[id(3,d,1)]=n+1;}
          else{v[id(0,-d,1)]=n+1;}
        }
        if(i==7){
          if(s<=A){v[id(0,s,1)]=n+1;}
          else{v[id(1,s-A,1)]=n+1;}
        }
        break;
      }
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  while(true){ solve(); }
}
