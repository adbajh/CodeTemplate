#include <bits/stdc++.h>
#define N (int)5e5 + 1
using namespace std;
 
struct graph
{
    int n, m;
    multiset<int> G[N];
    int degree[N];
 
    void init()
    {
        scanf("%d %d", &n, &m);
        for (int i = 0; i <= n; ++i)
            degree[i] = 0;
        int x, y;
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d%d", &x, &y);
            add_edge(x,y);
        }
    }
 
    void delete_edge(int u, int v)
    {
        auto it1 = (G[u]).find(v);
        if (it1 != (G[u]).end())
        {
            G[u].erase(it1);
            degree[u]--;
        }
        auto it2 = (G[v]).find(u);
        if (it2 != (G[v]).end())
        {
            G[v].erase(it2);
            degree[v]--;
        }
    }
 
    void add_edge(int u, int v)
    {
        G[u].insert(v);
        G[v].insert(u);
        degree[u]++;
        degree[v]++;
    }
 
    bool is_connected_without_islands()
    {
        int visited[n+1] = {};
        for (int i = 0; i <= n; ++i)
            visited[i] = 0;
        DFS(1,visited);
        for (int i = 1; i <= n; ++i)
            if (visited[i] == 0 && degree[i] > 0) return false;
        return true;
    }
 
    void DFS(int cur, int visited[])
    {
        visited[cur] = 1;
        for (int u : G[cur])
            if (visited[u] == 0)
                DFS(u,visited);
    }
 
    void find_Euler_Path(int start)
    {
        stack<int> EP;
        EP.push(start);
        int u, v;
        while (!EP.empty())
        {
            u = EP.top();
            if (degree[u])
            {
                v = *((G[u]).begin());
                EP.push(v);
                delete_edge(u,v);
            }
            else
            {
                printf("%d ",u);
                EP.pop();
            }
        }
        printf("\n");
    }
};
 
int main()
{
    int T;
    scanf("%d", &T);
    for (;T;--T)
    {
        //构造图
        struct graph A;
        A.init();
        //是否连通
        bool flag = A.is_connected_without_islands();
        //是否存在欧拉图 + 初始化起点终点
        int u = 1, v = 1;
        if (flag)
            for (int i = 1; i <= A.n; ++i) if (A.degree[i] % 2 == 1)
            {
                u = i;
                for (int j = i + 1; j <= A.n; ++j) if (A.degree[j] % 2 == 1)
                {
                    v = j;
                    for (int k = j + 1; k <= A.n; ++k) if (A.degree[k] % 2 == 1)
                    {
                        flag = false;
                        break;
                    }
                    break;
                }
                break;
            }
        //找路径
        if (flag)
        {
            printf("Yes\n");
            printf("%d\n", A.m + 1);
            A.find_Euler_Path(u);
        }
        else printf("No\n");
    }
    return 0;
}