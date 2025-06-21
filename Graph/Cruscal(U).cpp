#include <bits/stdc++.h>
 
using namespace std;
 
#define ll long long
#define N (int)2e5+1
#define M (int)5e5+1
 
struct edge {
    int u, v;
    ll w;
};
 
std::vector<std::pair<int,ll>> adj[N];
std::vector<edge> E;
int n, m;
 
void init() {
    scanf("%d%d", &n, &m);
    int u, v; ll w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%lld", &u, &v, &w);
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
        E.push_back({u,v,w});
    }
}
 
/********  Disjoint Set  ********/
 
int p[N], r[N], s[N];
 
void MakeSet(int x) {
    p[x] = x;
    r[x] = 0;
    s[x] = 1;
}
 
int FindSet(int x) {
    if (x != p[x])
        p[x] = FindSet(p[x]);
    return p[x];
}
 
void Link(int x, int y) {
    if (r[x] > r[y]) {
        p[y] = x;
        s[x] += s[y];
    }
    else {
        p[x] = y;
        s[y] += s[x];
        if (r[x] == r[y])
            r[y]++;
    }
}
 
void Union(int x, int y) {
    Link(FindSet(x), FindSet(y));
}

int FindSize(int x) {
    return s[FindSet(x)];
}
 
/********************************/
 
std::vector<edge> MST;
 
bool cmp(const edge a, const edge b) {
    return (a.w < b.w);
}
 
void Kruskal() {
    sort(E.begin(),E.end(),cmp);
    for (int v = 1; v <= n; v++)
        MakeSet(v);
    for (edge e : E) {
        if (FindSet(e.u) != FindSet(e.v)) {
            MST.push_back(e);
            Union(e.u,e.v);
            printf("%d\n",FindSize(e.u));
        }
    }
}
 
int main() {
    init();
    Kruskal();
    return 0;
}