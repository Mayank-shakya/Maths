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
  int  w,h,n;cin>>w>>h>>n;

  auto f=[&](int m)->bool{

    int ans=m/w;
    ans*=m/h;

    return ans>=n;

  };

  int lo=1,hi=n*max(h,w);
int ans=-1;
  while(lo<=hi){
    int m=(lo+hi)/2;

    if(f(m)){
      ans=m;
      hi=m-1;
    }else{
      lo=m+1;
    }

  }
  ///////
  assert(!(ans == -1));
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
