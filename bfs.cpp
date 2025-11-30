#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define F first
#define S second
#define endl '\n'



const int M=1e9+7;
const long long N=1e17+9;

vector<int>dis;
vector<int>vis;
vector<vector<int>>adj;

void solve() {
  int n,m;cin>>n>>m;
  adj.assign(n+1,vector<int>());
  dis.assign(n+1,1e9);
   vis.assign(n+1,0);
  for(int ii=0;ii<m;ii++){
    int a,b;cin>>a>>b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  int st=1,ed=n;

  dis[st]=0;
//   vis[st]=1;
  queue<int>q;
  q.push(st);

vector<int>par(n+1);
par[st]=-1;
  while(q.size()){
    auto it=q.front();q.pop();
    if(vis[it])continue;
    vis[it]=1;

    for(auto nb:adj[it]){
        if(!vis[nb] && dis[nb] > dis[it] + 1){
            
                    dis[nb]=1+dis[it];
                    q.push(nb);
                    par[nb]=it;

        }
    }
  }
if(dis[ed]==1e9){
    cout<<"IMPOSSIBLE"<<endl;
    return;
}
cout<<dis[ed]+1<<endl;
vector<int>path;
int ppr=n;
while(ppr != -1){
    path.push_back(ppr);
    ppr=par[ppr];
}
reverse(path.begin(),path.end());


for(auto it:path)cout<<it<<" ";


cout<<endl;



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
