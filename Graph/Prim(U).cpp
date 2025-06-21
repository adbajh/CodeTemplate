#include <bits/stdc++.h>
#define ll long long
#define ss short int
#define infty 2147483647
using namespace std;
 
int t[5001], b[5001];
#define wei(u,v) (int)min(t[u]^b[v],t[v]^b[u])
 
typedef pair<int, ss> PII;
 
ll Prim(ss n) {
    priority_queue<PII> pq;
    vector<bool> inMST(n + 1, false);
    vector<ss> parent(n + 1, 0);
    vector<int> mw(n + 1, 0);
 
    pq.push({infty, 1});
    mw[1] = 0;
    ll mst_weight = 0;
 
    for (int i = 0; i < n; i++) {
 
        while (inMST[pq.top().second])
            pq.pop();
        ss v = pq.top().second;
        pq.pop();
        inMST[v] = 1;
 
        if (v != 1)
            mst_weight += wei(parent[v],v);
         
        for (ss w = 1; w < v; w++) {
            if (!inMST[w] && wei(v,w) > mw[w]) {
                mw[w] = wei(v,w);
                parent[w] = v;
                pq.push({mw[w],w});
            }
        }
        for (ss w = v + 1; w <= n; w++) {
            if (!inMST[w] && wei(v,w) > mw[w]) {
                mw[w] = wei(v,w);
                parent[w] = v;
                pq.push({mw[w],w});
            }
        }
    }
 
    return mst_weight;
}
 
int main() {
    ss n;
    scanf("%hd", &n);
    for (ss i = 1; i <= n; i++)
        scanf("%d%d", &t[i], &b[i]);
 
    ll sum = Prim(n);
    printf("%lld", sum);
 
    return 0;
}