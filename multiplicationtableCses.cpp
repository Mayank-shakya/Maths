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
  int n;cin>>n;
  int k=(n*n+1)/2;



  int ans=-1;

// noe <=x >=k
auto f=[&](int m)->bool{

  int totel=0;

  for(int ro=1;ro<=n;ro++){
    

    int noOfelemInthisRow=min(n,m/ro);
    totel+=noOfelemInthisRow;

    if(totel>=k)return 1;

  }
return totel>=k;
};



  int lo=0,hi=n*n;

  while(lo<=hi){
    int m=(lo+hi)/2;

    if(f(m)){
      hi=m-1;
      ans=m;
    }else{
      lo=m+1;
    }

  }
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
