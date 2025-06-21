#include <bits/stdc++.h>
 
using namespace std;
 
#define N 501
#define infty (1<<30)
 
int n, w[N][N], h[N];
 
vector<pair<int,int>> G[N];

void init() {
    scanf("%d",&n);
    for (int i = 1; i <= n; i++)
        G[0].emplace_back(i,0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            scanf("%d", &w[i][j]);
            G[i].emplace_back(j,w[i][j]);
        }
}
 
int d[N][N];
#define relax(u,v,s) do { \
if (d[s][v] > d[s][u] + w[u][v]) \
    d[s][v] = d[s][u] + w[u][v]; \
} while (0)
 
void BellmanFold(int s) {
    for (int i = 0; i <= n; i++)
        d[s][i] = infty;
    d[s][s] = 0;
 
    for (int i = 1; i <= n; i++)
        for (int u = 0; u <= n; u++)
            for (const auto &[v,weight] : G[u])
                relax(u,v,s);
}
 
#define W(u,v) w[u][v]
#define h(u) W(0,u)
#define Wi(u,v) (W(u,v) + h(u) - h(v))
 
void dijkstra(int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 1; i <= n; i++)
        d[src][i] = infty;
    d[src][src] = 0;
    pq.push({0, src});
 
    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();
 
        if (current_dist > d[src][u]) continue;
 
        for (const auto &[v, weight] : G[u]) {
            if (d[src][u] + Wi(u,v) < d[src][v]) {
                d[src][v] =d[src][u] + Wi(u,v);
                pq.push({d[src][v], v});
            }
        }
    }
}
 
void Johnson() {
    BellmanFold(0);
 
    for (int i = 1; i <= n; i++) {
        dijkstra(i);
        for (int j = 1; j <= n; j++)
            d[i][j] = d[i][j] + h(j) - h(i);
    }
}
 
int main() {
    init();
    Johnson();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            printf("%d ", d[i][j]);
        printf("\n");
    }
}