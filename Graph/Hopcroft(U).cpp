#include <bits/stdc++.h>
 
using namespace std;
 
class BG {
 
#define _N 20001
#define infty (int)(1<<30)
 
public:
    int n, nl, nr, e; // nl 为左半部分顶点数，nr 为右半部分顶点数，e 为边数 (可以包含重边)
    int degree[_N];
    std::vector<int> adj[_N];

    void init() {
        scanf("%d%d%d", &nl, &nr, &e);
        n = nl + nr;
        for (int i = 0; i <= n; i++) {
            degree[i] = 0; // 初始化 degree 为 0
            adj[i].clear(); // 清空邻接表
        }
        int l, r;
        for (int i = 0; i < e; i++) {
            scanf("%d%d", &l, &r);
            degree[l]++;
            degree[r + nl]++;
            adj[l].push_back(r + nl); // 左边顶点连右边顶点
            adj[r + nl].push_back(l); // 右边顶点连回左边顶点
        }
    }

    void FindMatch() {
        // 初始化匹配数组
        for (int i = 0; i <= n; i++) {
            match[i] = 0;
        }
        size_of_match = 0;
        while (BFS()) { // BFS 阶段：寻找层次图
            for (int u = 1; u <= nl; u++) {
                if (match[u] == 0 && DFS(u)) { // DFS 阶段：寻找增广路径
                    size_of_match++;
                }
            }
        }
        // 输出最大匹配的大小
        printf("%d\n", size_of_match);
    }

private:
    int match[_N], dist[_N]; // match 保存每个点的匹配状态，dist 保存距离信息
    int size_of_match; // 最大匹配数

    // BFS：构建层次图，返回是否存在增广路径
    bool BFS() {
        std::queue<int> q;
        for (int u = 1; u <= nl; u++) {
            if (match[u] == 0) { // 左侧未匹配的点加入队列
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = infty;
            }
        }
        dist[0] = infty; // 0 表示哨兵，表示不匹配的节点
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] < dist[0]) {
                for (int v : adj[u]) {
                    if (dist[match[v]] == infty) { // 找到未处理过的匹配边
                        dist[match[v]] = dist[u] + 1;
                        q.push(match[v]);
                    }
                }
            }
        }
        return dist[0] != infty; // 是否找到了增广路径
    }

    // DFS：寻找增广路径并更新匹配关系
    bool DFS(int u) {
        if (u != 0) {
            for (int v : adj[u]) {
                if (dist[match[v]] == dist[u] + 1 && DFS(match[v])) {
                    match[u] = v;
                    match[v] = u;
                    return true;
                }
            }
            dist[u] = infty; // 如果未找到增广路径，将该点标记为不可达
            return false;
        }
        return true;
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