#include <bits/stdc++.h>
#define N (int)5e3 + 1
using namespace std;
 
struct Graph {
    int n, m;
    multiset<int> adj[N];
    int degree[N];

    void clear() {
        m = 0;
        memset(degree,0,sizeof(degree));
        for (int i = 0; i < N; i++) adj[i].clear();
    }

    void add_edge(int u, int v) {
        m++;
        adj[u].insert(v);
        adj[v].insert(u);
        degree[u]++;
        degree[v]++;
    }
 
    void delete_edge(int u, int v) {
        auto it1 = (adj[u]).find(v);
        if (it1 != (adj[u]).end()) {
            adj[u].erase(it1);
            degree[u]--;
        } else {
            return;
        }
        auto it2 = (adj[v]).find(u);
        if (it2 != (adj[v]).end()) {
            adj[v].erase(it2);
            degree[v]--;
        } else {
            return;
        }
        m--;
    }
} graph;

void init(Graph &G) {
    int m;
    G.clear();
    scanf("%d%d", &G.n, &m);
    int x, y;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &x, &y);
        G.add_edge(x,y);
    }
}

/***** 寻找欧拉迹 *****/

void Euler_DFS(const Graph &G, int u, bool vst[]) {
    vst[u] = true;
    for (int v : G.adj[u])
        if (!vst[v])
            Euler_DFS(G,v,vst);
}

bool find_Euler_Path(Graph G, std::vector<int> &path) {
    path.clear();
    // 除去孤立点外，判断是否连通
    bool EP_vst[N];
    memset(EP_vst,0,sizeof(EP_vst));
    Euler_DFS(G,1,EP_vst);
    for (int i = G.n; i >= 1; i--)
        if (EP_vst[i] == false && G.degree[i] > 0)
            return false;
    // 判断是否存在欧垃迹，若存在则给出起始点
    int start = 1, sum_of_odd = 0;
    for (int i = G.n; i >= 1; i--) {
        if (G.degree[i] & 1) {
            start = i;
            sum_of_odd++;
        }
    }
    if (sum_of_odd != 0 && sum_of_odd != 2)
        return false;
    // 寻找欧拉迹
    int u, v;
    stack<int> EP;
    EP.push(start);
    while (!EP.empty()) {
        u = EP.top();
        if (G.degree[u]) {
            v = *(G.adj[u].begin());
            EP.push(v);
            G.delete_edge(u,v);
        } else {
            path.push_back(u);
            EP.pop();
        }
    }
    return true;
}
 
int main() {
    int T;
    scanf("%d", &T);
    vector<int> path;
    for (;T;--T) {
        //构造图
        init(graph);
        if (find_Euler_Path(graph,path)) {
            printf("Yes\n");
            printf("%d\n",path.size());
            for (int u : path) printf("%d ",u);
            printf("\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}