long long dist[100100];
bool vis[100100];

void dijkstra(int src) {

    for(int i = 1; i <= n; i++){
        dist[i] = INF;
        vis[i] = 0;
    }

    priority_queue<pair<long long,int>> pq;  // max-heap

    dist[src] = 0;
    pq.push({-0, src});    // -dist[src] = 0

    while(!pq.empty()) {
        auto [negd, u] = pq.top();
        pq.pop();

        if(vis[u]) continue;
        vis[u] = true;

        for(auto it: adj[u]) {
            auto [nb, wt] = it;

            if(dist[nb] > dist[u] + wt) {
                dist[nb] = dist[u] + wt;
                pq.push({-dist[nb], nb});   // negative push for min-heap behavior
            }
        }
    }
}
