#include <bits/stdc++.h>
#define N 501
#define infty 0x3FFFFFFFFFFFFFFFLL
typedef long long ll;
using namespace std;

struct Graph {
    int n, m;
    std::vector<vector<pair<int,ll>>> adj;
    std::vector<int> degree;

    void init(int _n) {
        n = _n;
        m = 0;
        degree.clear();
        degree.resize(_n + 1);
        for (int i = 0; i <= _n; i++) degree[i] = 0;
        adj.clear();
        adj.resize(_n + 1);
    }

    void add_edge(int u, int v, ll w) {
        degree[u]++;
        adj[u].emplace_back(v,w);
        m++;
    }
} graph;

bool BellmanFold(const Graph &G, int src, ll dist[]) {
    int n = G.n;
    for (int i = 1; i <= n; i++) dist[i] = infty;
    dist[src] = 0;
    for (int i = 1; i < n; i++)
        for (int u = 1; u <= n; u++)
            for (auto &[v,w] : G.adj[u])
                if (dist[v] > dist[u] + w)
                    dist[v] = dist[u] + w;
    for (int u = 1; u <= n; u++)
        for (auto &[v,w] : G.adj[u])
            if (dist[v] > dist[u] + w)
                return false;
    return true;
}

void Dijkstra(const Graph &G, int src, ll dist[]) {
    int n = G.n;
    typedef pair<ll,int> PII;
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    for (int i = 1; i <= n; i++) dist[i] = infty;
    dist[src] = 0;
    pq.push({0LL,src});
    while (!pq.empty()) {
        auto [cur_dist,u] = pq.top();
        pq.pop();
        if (cur_dist > dist[u]) continue;
        for (auto &[v,w] : G.adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

bool Johnson(const Graph &G, ll *dist[]) {
    Graph new_G;
    int n = G.n;
    int s = G.n + 1;
    new_G.n = s;
    new_G.m = G.m;
    new_G.adj = G.adj;
    new_G.degree = G.degree;
    new_G.adj.push_back({});
    new_G.degree.push_back(0);
    for (int i = 1; i < s; i++) {
        new_G.add_edge(s,i,0LL);
    }
    ll h[s+1];
    if (!BellmanFold(new_G,s,h)) return false;
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < new_G.adj[u].size(); i++) {
            int v = new_G.adj[u][i].first;
            new_G.adj[u][i].second += h[u] - h[v];
        }
    }
    for (int u = 1; u <= n; u++) {
        Dijkstra(new_G,u,dist[u]);
        for (int v = 1; v <= n; v++) {
            dist[u][v] += h[v] - h[u];
        }
    }
    return true;
}

void test_single_pair() {
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    graph.init(n);
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        scanf("%d%d%lld", &u, &v, &w);
        graph.add_edge(u,v,w);
        graph.add_edge(v,u,w);
    }
    ll dist[n+1];
    BellmanFold(graph,s,dist);
    for (int i = 1; i <= n; i++) {
        printf("%lld ",dist[i]);
    }
}

void test_all_pair() {
    int n;
    scanf("%d", &n);
    ll w, D[n+1][n+1];
    ll *dist[n+1];
    graph.init(n);
    for (int i = 0; i <= n; i++) dist[i] = D[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%lld", &w);
            graph.add_edge(i,j,w);
        }
    }
    Johnson(graph,dist);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%lld ", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    test_all_pair();
    return 0;
}