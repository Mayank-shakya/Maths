#include <bits/stdc++.h>
#define int long long
using namespace std;
struct HP {
    int nL,nR;
    vector<vector<int>>adj; 
    vector<int>dist,pairU,pairV;

    HP(int _nL,int _nR):nL(_nL),nR(_nR) {
        adj.assign(nL,{});
        pairU.assign(nL,-1);
        pairV.assign(nR,-1);
        dist.assign(nL,0);
    }

    void addEdge(int u,int v) { 
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int>q;
        const int INF=1e9;
        for (int u=0;u<nL;++u){
            if (pairU[u]==-1) {
                dist[u]=0;
                q.push(u);
            } else{
                dist[u]=INF;}
            
        }
        bool rFV=false;
        while(!q.empty()){
            int u=q.front();q.pop();
            for (int v:adj[u]) {
                int pu=pairV[v];
                if (pu==-1){
                    rFV=true;
                } else if(dist[pu]==INF){
                    dist[pu] = dist[u]+1;
                    q.push(pu);
                }
            }
        }
        return rFV;
    }

    bool dfs(int u){
        for (int v:adj[u]){
            int pu=pairV[v];
            if (pu==-1||(dist[pu]==dist[u]+1 && dfs(pu))){
                pairU[u]=v;
                pairV[v]=u;
                return true;
            }
        }
        dist[u]=INT_MAX; 
        return false;
    }

    int maxMat(){
        int ress=0;
        while(bfs()){
            for (int u=0;u<nL;++u) {
                if (pairU[u]==-1){
                    if(dfs(u))++ress;
                }
            }
        }
        return ress;
    }
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int N;
    if (!(cin>>N)) {
        return 0; 
    }
    struct rC {int x,y,d;};
    vector<rC> r(N);
    for (int i=0;i<N;++i){
        cin>>r[i].x>>r[i].y>>r[i].d;
    }

    HP hk(N, N);
    for (int i=0;i<N;++i) {
        for (int j=0;j<N;++j) {
            if (i==j)continue;
            if (r[j].d<=r[i].d)continue; 
            int md = abs(r[i].x - r[j].x)+abs(r[i].y-r[j].y);
            if (r[j].d-r[i].d>=md) {
                hk.addEdge(i, j);
            }
        }
    }
    int match=hk.maxMat();
    int minCars=N-match;
    cout<<minCars;
    return 0;
}