#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
const int M=1e9+7;
const int N = 1e6+5;
 
int fact[N];
int invfact[N];
 
int preK=0;
 
int binpow(int a,int b,int m){
    if(b==0)return 1;
    if(b%2==1){
        return (a%m*binpow(a,b-1,m)%m)%m;
    }
    else{
        int temp = binpow(a,b/2,m);
        return (temp%m*temp%m)%m;
    }
}
 
void pre(){
    if(preK)return;
    preK=1;
 
    fact[0]=fact[1]=1;
    for(int i=2;i<N;i++){
        fact[i]=(fact[i-1]%M*i%M)%M;
    }
 
        invfact[N-1]=binpow(fact[N-1],M-2,M);
 
    for(int i=N-2;i>=0;i--){
        invfact[i]=(invfact[i+1]%M*(i+1)%M)%M;
    }
 
    
}
 
 
#define endl '\n'
 
void solve() {
  int a, b;cin>>a>>b;
 
  int comb =( (fact[a]%M*invfact[a-b]%M)%M*invfact[b]%M)%M;
 
  cout<<comb<<endl;
  
 
 
}
 
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    pre();
 
    int t=1;
    cin >> t;
    while (t--) solve();
    return 0;
}