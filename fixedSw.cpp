#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define F first
#define S second
#define endl '\n'



const int M=1e9+7;
const long long N=1e17+9;

 int dis;
int fq[1000004];

void pr(){
    dis=0;
    memset(fq, 0, sizeof(fq));
}
void add(int x){
        fq[x]++;
        if(fq[x]==1)dis++;
    }
    void rem(int x){
        fq[x]--;
        if(fq[x]==0)dis--;
    }

    int get(){
        return dis;
    }


void solve() {
    
     
  int n,d;
  cin>>n>>d;
  vector<int>v(n);
  for(auto &i:v)cin>>i;

  int ans=n;
 

  for(int i=0;i<n;i++){
    add(v[i]);
    if(i-d>=0)rem(v[i-d]);///
    if(i>=d-1)ans=min(ans,get());///
  }

  for(int i=n-d;i<n;i++){
    rem(v[i]);///
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

    pr();
    
    int _t=1;
    cin >> _t;
    while (_t--){
        solve();
    }
    return 0;
}
