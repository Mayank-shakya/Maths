#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define F first
#define S second
#define endl '\n'



const int M=1e9+7;
const long long N=1e17+9;

int D;

struct DS{

    int dis;
    int fq[1001000];

    
    DS(){
        dis = 0;
        memset(fq, 0, sizeof(fq));///
    }



    void add(int x){
        fq[x]++;
        if(fq[x]==1)dis++;
    }
    void rem(int x){
        fq[x]--;
        if(fq[x]==0)dis--;
    }

    bool can(int h1,int t){
        return h1-t+1<=D;
    }

    int get(){
        return dis;
    }

};

void solve() {
  int n,d;
  cin>>n>>d;
  vector<int>v(n);
  for(auto &i:v)cin>>i;
D=d;
  int ans=n;
  DS ds;

  for(int i=0;i<n;i++){
    ds.add(v[i]);
    if(i-d>=0)ds.rem(v[i-d]);///
    if(i>=d-1)ans=min(ans,ds.get());///
  }



  cout<<ans<<endl;




//   int head=-1,tail=0;

//   while(tail<n){

//     while(head+1<n && ds.can(head+1,tail)){
//         head++;
//         ds.add(v[head]);
//     }
//     if(head+1>=n)break;

//     ans=min(ans,ds.get());
//     // cout<<ans<<endl;

//     if(tail<=head){
//         ds.rem(v[tail]);
//         tail++;
//     }else{
//         tail++;
//         head=tail-1;
//     }
//   }

//   cout<<ans<<endl;




}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    
    int _t=1;
    cin >> _t;
    while (_t--){
        solve();
    }
    return 0;
}
