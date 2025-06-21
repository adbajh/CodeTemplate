#include <bits/stdc++.h>
using namespace std;
 
class BG {
 
#define _L 2001
#define _R 2001
#define _N 4001
#define infty (int)(1<<30)
 
public:
    int n, nl, nr, e; // nl为左半部分顶点数，nr为右半部分顶点数，e为边数(可以包含重边) 
    int degree[_N];
    vector<int> adj[_N];
 
    struct node {
        int u;
        node* nxt;
    };
 
    void init() {
        scanf("%d%d%d", &nl, &nr, &e);
        n = nl + nr;
        for (int i = 0; i <= n; i++)
            degree[i]++;
        int l, r;
        for (int i = 0; i < e; i++) {
            scanf("%d%d", &l, &r);
            degree[l]++;
            degree[r + nl]++;
            adj[l].push_back(r + nl); // 标号为1-nl的点在左半部分，标号为nl+1的点在右半部分 
            adj[r + nl].push_back(l);
        }
    }
 
    void FindMatch() {
        // 使用匈牙利算法计算最大匹配
        size_of_match = 0;
        fill(match, match + _N, -1); // 初始化匹配数组
 
        for (int u = 1; u <= nl; u++) {
            fill(visited, visited + _N, false);
            if (dfs(u)) // 如果找到增广路径，增加匹配数
                size_of_match++;
        }
 
        // 输出最大匹配数
        printf("%d\n", size_of_match);
    }
 
private:
    int match[_N], size_of_match;
    bool visited[_N];
 
    bool dfs(int u) {
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = true;
                if (match[v] == -1 || dfs(match[v])) {
                    match[u] = v;
                    match[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    int T, n, m, e;
    for (scanf("%d",&T);T;--T) {
        BG graph;
        graph.init();
        graph.FindMatch();
    }
    return 0;
}