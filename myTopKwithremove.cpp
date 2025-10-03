#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long


const int M=1e9+7;
const long long N=1e17+9;



void solve() {
  int q,k;cin>>q>>k;

  multiset<int>lo,hi;
  int sumK=0;

    auto bal=[&]()->void{
        while(lo.size()>k){
            int x=*lo.begin();
            lo.erase(lo.begin());
            sumK-=x;
            hi.insert(x);
        }

        while(lo.size()<k && hi.size()){
            int x=*hi.rbegin();
            lo.insert(x);
            sumK+=x;
            auto it=hi.end();it--;
            hi.erase(it);
        }
    };
    auto rem=[&](int x)->void{
        if(lo.find(x) != lo.end()){
            lo.erase(lo.find(x));
            sumK-=x;
        }else if(hi.find(x) != hi.end()){
            hi.erase(hi.find(x));
        }
        bal();
    };
    auto add=[&](int x)->void{
        if(*lo.begin()<=x){
            sumK+=x;
            lo.insert(x);
        }else{
            hi.insert(x);
        }
        bal();
    };

  while(q--){
    int num;cin>>num;

    if(num==1){
        int x;cin>>x;

        add(x);
    }else if(num==2){
        int x;cin>>x;

        rem(x);
    }else if(num==3){
        char x;cin>>x;
        
        cout<<sumK<<endl;
    }
  }
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
