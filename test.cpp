#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define F first
#define S second
#define endl '\n'



const int M=1e9+7;
const long long N=1e17+9;



void solve() {
  int n,k;cin>>n>>k;
  vector<int>v(n);
  int ans=-1;
  for(auto &i:v)cin>>i;

  auto f=[&](int m)->bool{
    int nos=0;
    int slef=0;

    for(int i=0;i<n;i++){
      if(slef>=v[i]){
        slef-=v[i];
      }else{
        nos++;
        slef=m;
        i--;
        if(nos>k)return 0;
      }
    }
    return nos<=k;
  };

 int lo=1,hi=1e10;

  while(lo<=hi){
    int m=(lo+hi)/2;

    if(f(m)){
      hi=m-1;
      ans=m;
    }else{
lo=m+1;
    }
  }
// if(ans==-1) ?
  cout<<ans<<endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    
    int _t=1;
    // cin >> _t;
    while (_t--){
        solve();
    }
    return 0;
}
