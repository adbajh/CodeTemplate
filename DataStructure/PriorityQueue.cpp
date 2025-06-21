#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool DefaultCmp(ll a, ll b) {
    return a <= b;
}

class PriorityQueue { // 默认是最小堆
public:
    PriorityQueue() {
        heap_cmp = DefaultCmp;
        Num.clear();
        heap_size = 0;
        Num.push_back(0);
    }
    PriorityQueue(bool (*_cmp)(ll,ll)) {
        heap_cmp = _cmp;
        Num.clear();
        heap_size = 0;
        Num.push_back(0);
    }
    int size() {
        return heap_size;
    }
    bool empty() {
        return heap_size == 0;
    }
    void clear() {
        Num.clear();
        heap_size = 0;
        Num.push_back(0);
    }
    void push(ll x) {
        Num.push_back(x);
        heap_size++;
        Heapify_Up(heap_size);
    }
    ll top() {
        if (heap_size == 0) {
            printf("Empty Heap!\n");
            return INT_MIN;
        }
        return Num[1];
    }
    void pop() {
        if (heap_size == 0) {
            printf("Empty Heap!\n");
            return;
        }
        Num[1] = Num[heap_size];
        Num.pop_back();
        heap_size--;
        Heapify_Down(1);
    }
    void insert_array(std::vector<ll> arr) {
        Num.insert(Num.end(),arr.begin(),arr.end());
        heap_size += arr.size();
        for (int i = (heap_size >> 1); i >= 1; i--)
            Heapify_Down(i);
    }
private:
    vector<ll> Num;
    int heap_size;
    bool (*heap_cmp)(ll,ll);
    void Heapify_Up(int idx) {
        while (idx > 1) {
            int pa = idx >> 1;
            if (heap_cmp(Num[pa],Num[idx])) break;
            ll tem = Num[pa];
            Num[pa] = Num[idx];
            Num[idx] = tem;
            idx = pa;
        }
    }
    void Heapify_Down(int idx) {
        int limit = heap_size >> 1;
        while (idx <= limit) {
            int max_idx = idx;
            int l = idx << 1;
            int r = l + 1;
            if (l <= heap_size && !heap_cmp(Num[max_idx],Num[l])) max_idx = l;
            if (r <= heap_size && !heap_cmp(Num[max_idx],Num[r])) max_idx = r;
            if (max_idx == idx) break;
            ll tem = Num[max_idx];
            Num[max_idx] = Num[idx];
            Num[idx] = tem;
            idx = max_idx;
        }
    }
};

int main() {
    PriorityQueue pq;
    vector<ll> arr;
    for (int i = 0; i < 20; i++) arr.push_back(rand()%100);
    for (ll x : arr) printf("%lld ",x);
    printf("\n");
    pq.insert_array(arr);
    while (!pq.empty()) {
        printf("%lld ", pq.top());
        pq.pop();
    }
    printf("\n");
    sort(arr.begin(),arr.end());
    for (ll x : arr) printf("%lld ", x);
    return 0;
}