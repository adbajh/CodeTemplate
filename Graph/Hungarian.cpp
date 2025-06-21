#include <bits/stdc++.h>
using namespace std;

struct BiGraph {

#define _NN 4001

    int n, nl, nr, e; // nl为左半部分顶点数，nr为右半部分顶点数，e为边数(可以包含重边) 
    int degree[_NN];
    vector<int> adj[_NN];

    void clear() {
        n = nl = nr = e = 0;
        memset(degree, 0, sizeof(degree));
        for (int i = 0; i < _NN; i++) adj[i].clear();
    }
};

void init_graph(BiGraph &G) {
    G.clear();
    int n, nl, nr, e;
    scanf("%d%d%d", &nl, &nr, &e);
    G.nl = nl, G.nr = nr, G.e = e;
    G.n = nl + nr;
    int l, r;
    for (int i = 0; i < e; i++) {
        scanf("%d%d", &l, &r);
        G.degree[l]++;
        G.degree[r+nl]++;
        G.adj[l].push_back(r+nl);
        G.adj[r+nl].push_back(l);
    }
}

/****** 匈牙利算法 ******/

bool Match_DFS(const BiGraph& G, bool vst[], int match[], int u) {
    for (int v : G.adj[u]) {
        if (!vst[v]) {
            vst[v] = true;
            if (match[v] == -1 || Match_DFS(G,vst,match,match[v])) {
                match[u] = v;
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

void FindMatch(const BiGraph &G, int match[], int &size_of_match) {
    size_of_match = 0;
    fill(match, match + _NN, -1);
    bool Match_vst[G.n+1];
    for (int u = 1; u <= G.nl; u++) {
        memset(Match_vst, 0, sizeof(Match_vst));
        if (Match_DFS(G,Match_vst,match,u)) size_of_match++;
    }
}

BiGraph graph;
 
int main() {
    int T, n, m, e;
    int match[_NN], size_of_match;
    for (scanf("%d",&T);T;--T) {
        init_graph(graph);
        FindMatch(graph,match,size_of_match);
        printf("%d\n",size_of_match);
        for (int i = 1; i <= graph.nl; i++) {
            if (match[i] != -1) {
                printf("%d %d\n",i,match[i]);
            }
        }
    }
    return 0;
}