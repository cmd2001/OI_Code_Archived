#pragma GCC optimize(3)
#include<cstdio>
#include<cstring>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;
const int maxn=1e5+1e2,maxm=1e6+1e2;

struct Node {
    int dis,pos;
    friend bool operator < (const Node &a,const Node &b) {
        return a.dis > b.dis;
    }
};
typedef __gnu_pbds::priority_queue<Node,less<Node>,pairing_heap_tag> Heap;
typedef __gnu_pbds::priority_queue<Node,less<Node>,pairing_heap_tag>::point_iterator Iterator;

Heap heap;
int s[maxn],t[maxm<<1],nxt[maxm<<1],l[maxm<<1],dis[maxn],vis[maxn];
Iterator it[maxn];

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}

inline void dji() {
    memset(dis,0x3f,sizeof(dis)) , dis[1] = 0;
    it[1] = heap.push((Node){dis[1],1});
    while( heap.size() ) {
        const int pos = (heap.top()).pos; heap.pop() , it[pos] = NULL;
        for(int at=s[pos];at;at=nxt[at])
            if( dis[t[at]] > dis[pos] + l[at] ) {
                dis[t[at]] = dis[pos] + l[at];
                if( it[t[at]] != NULL ) heap.modify(it[t[at]],(Node){dis[t[at]],t[at]});
                else it[t[at]] = heap.push((Node){dis[t[at]],t[at]});
            }
    }
}
 

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b,l;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&l);
        addedge(a,b,l);
    }
    dji();
    printf("%d\n",dis[n]);
    return 0;
}

