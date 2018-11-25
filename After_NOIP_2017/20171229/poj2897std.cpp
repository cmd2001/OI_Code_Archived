#include <cstdio>  
#include <cstring>  
#include <algorithm>  
#include <iostream>  
#include <vector>  
#include <queue>  
  
#define T (n + 1)  
  
const long long INF = 1e16;  
  
using namespace std;  
  
struct Edge{  
    int from, to;  
    long long cap;  
    Edge() {}  
    Edge(int a, int b, long long c) : from(a), to(b), cap(c) {}  
};  
  
int n, m;  
vector<Edge> edges;  
vector<int> G[5005];  
  
void addEdge(int from, int to, long long cap) {  
    edges.push_back(Edge(from, to, cap));  
    edges.push_back(Edge(to, from, 0));  
    int siz = edges.size();  
    G[from].push_back(siz - 2);  
    G[to].push_back(siz - 1);  
}  
  
int cur[5005];  
int layer[5005];  
  
bool build() {  
    memset(layer, -1, sizeof(layer));  
    queue<int> q;  
    layer[0] = 0;  
    q.push(0);  
    while (!q.empty()) {  
        int current = q.front();  
        q.pop();  
        for (int i = 0; i < G[current].size(); i++) {  
            Edge e = edges[G[current][i]];  
            if (layer[e.to] == -1 && e.cap > 0) {  
                layer[e.to] = layer[current] + 1;  
                q.push(e.to);  
            }  
        }  
    }  
    return layer[T] != -1;  
}  
  
long long find(int x, long long curFlow) {  
    if (x == T || !curFlow) return curFlow;  
    long long flow = 0, f;  
    for (int &i = cur[x]; i < G[x].size(); i++) {  
        Edge &e = edges[G[x][i]];  
        if (layer[e.to] == layer[x] + 1  
            && (f = find(e.to, min(curFlow, e.cap)))) {  
            e.cap -= f;  
            edges[G[x][i] ^ 1].cap += f;  
            flow += f;  
            curFlow -= f;  
            if (!curFlow) break;  
        }  
    }  
    return flow;  
}  
  
long long dinic() {  
    long long ans = 0;  
    while (build()) {  
        memset(cur, 0, sizeof(cur));  
        ans += find(0, INF);  
    }  
    return ans;  
}  
  
int main() {  
    while (~scanf("%d %d", &n, &m)) {  
        for (int i = 0; i <= n; i++)  
            G[i].clear();  
        edges.clear();  
        int a, b;  
        long long x;  
        long long sum = 0, num = 0;  
        long long k = 6000;  
        for (int i = 1; i <= n; i++) {  
            cin >> x;  
            if (x > 0) {  
                sum += x;  
                num++;  
                addEdge(0, i, (long long)x * k - 1);  
            } else addEdge(i, T, (long long)-x * k + 1);  
        }  
        for (int i = 0; i < m; i++) {  
            scanf("%d %d", &a, &b);  
            addEdge(a, b, INF);  
        }  
        long long maxFlow = dinic();  
        cout << (maxFlow + num) % k << ' ' << sum - (maxFlow + num) / k << endl;  
    }  
    return 0;  
}  
