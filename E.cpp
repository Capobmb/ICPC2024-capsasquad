#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,fma,popcnt,bmi,bmi2")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


void solve(ll n) {
    vector<int> c(n);
    for(int i=0;i<n;i++) cin >> c[i];
    vector<vector<int>> ans(n,vector<int>(n,0));
    bool YES=false;
    int lc=c[0],rc=c[n-1];

    if(lc==rc){
        YES=true;
        for(int i=0;i<n;i++){
            ans[n-1][i]=c[i];
            ans[0][n-1-i]=c[i];
            ans[i][0]=c[i];
            ans[n-1-i][n-1]=c[i];
        }
    }

    else if(n==4){
        if(c[0]==c[2]&&c[1]==c[3]){
            YES=true;
            for(int i=1;i<=2;i++){
                ans[n-1][i]=c[i];
                ans[0][n-1-i]=c[i];
                ans[i][0]=c[i];
                ans[n-1-i][n-1]=c[i];
            }
        }

    }
    else{
        int lclast=-1,rcfirst=-1;
        for(int i=1;i<n-1;i++){
            if(c[i]==rc){
                rcfirst=i;
                break;
            } 
        }
         for(int i=n-2;i>=1;i--){
            if(c[i]==lc){
                lclast=i;
                break;
            } 
        }
        //cout << rcfirst << ' '<<lclast<<endl;


        if(lclast!=-1&&rcfirst!=-1&&lclast>rcfirst){
            YES=true;
            for(int i=rcfirst;i<=lclast;i++){
                ans[n-1][i]=c[i];
                ans[0][n-1-i]=c[i];
                ans[i][0]=c[i];
                ans[n-1-i][n-1]=c[i];
            }
            //87
            for(int i=1;i<rcfirst;i++){
                ans[i][n-1-lclast]=c[i];
                ans[n-1-i][lclast]=c[i];
                ans[lclast][i]=c[i];
                ans[n-1-lclast][n-1-i]=c[i];
            }

            //653
            for(int i=lclast+1;i<n-1;i++){
                ans[i][rcfirst]=c[i];
                ans[n-1-i][n-1-rcfirst]=c[i];
                ans[n-1-rcfirst][i]=c[i];
                ans[rcfirst][n-1-i]=c[i];
            }
        }
    }

    if(YES){
        cout << "YES"<<endl;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout << ans[i][j]<<' ';
            }
            cout << endl;
        }
    }
    else{
        cout << "No"<<endl;
    }

    
    

}

int main() {
    while(true) {
        // input
        ll n; cin>>n;
        if(n == 0) break;
        solve(n);
    }
}