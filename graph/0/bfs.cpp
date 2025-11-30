void bfs(int src) {
    for (int i = 1; i <= n; ++i) dist[i] = INF;

    queue<int> q;
    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v : adj[u]) {
            if (dist[v] == INF) {          // not discovered yet
                dist[v] = dist[u] + 1;     // weight = 1
                q.push(v);
            }
        }
    }
}