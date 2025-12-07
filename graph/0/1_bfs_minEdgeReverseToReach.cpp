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

    int n,m;cin>>n>>m;

    vector<pair<int,int>>adj[n+1];
    vector<int>dis(n+1);

    for(int i=1;i<=n;i++)dis[i]=M;

    for(int i=0;i<m;i++){
        int a,b;cin>>a>>b;
        adj[a].push_back({b,0});
        adj[b].push_back({a,1});
    }
  

    deque<int>dq;
    dq.push_back(1);
    dis[1]=0;

    while(dq.size()){
        auto nn=dq.front();dq.pop_front();

        for(auto it:adj[nn]){
            int nb=it.F,wt=it.S;
            if(dis[nb]>dis[nn]+wt){
                dis[nb]=dis[nn]+wt;
                if(wt==0){
                    dq.push_front(nb);
                }else{
                    dq.push_back(nb);
                }
            }

        }

        
    }

    if(dis[n]==M){
        cout<<-1<<endl;
    }else{
        cout<<dis[n]<<endl;
    }
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
