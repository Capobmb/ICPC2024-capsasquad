#include<bits/stdc++.h>
using namespace std;
using ll=long long;



int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
   vector<int> X(N),Y(N);
  for(int i=0;i<N;i++) cin >> X[i]>>Y[i];
  for(int i=0;i<N;i++){
    if(X[i]*Y[i]<0){
      cout << max(abs(X[i]),abs(Y[i])) << endl;
    }
    else{
      cout << abs(X[i])+abs(Y[i])<<endl;
    }

  }
  

}


