#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn*3],nxt[maxn*3],l[maxn*3],dis[maxn];
bool vis[maxn],pr[maxn],ne[maxn];
int n;

struct Node {
    int dis,pos;
    friend bool operator < (const Node &a,const Node &b) {
        return a.dis > b.dis;
    }
};
priority_queue<Node> pq;

inline void addedge(int from,int to,int len) {
    static int cnt;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dji() {
    memset(dis,0x3f,sizeof(int)*(n+2)) , pq.push((Node){0,1});
    while( pq.size() ) {
        const int pos = pq.top().pos , dd = pq.top().dis; pq.pop();
        if( vis[pos] ) continue;
        vis[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) if( dis[t[at]] > dd + l[at] ) pq.push((Node){dis[t[at]]=dd+l[at],t[at]});
    }
}

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0; char ch;
    while( !isdigit(ch=nextchar()) ) ;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    n = getint();
    for(int i=1,x;i<=n;i++) {
        x = getint();
        if( i + x <= n ) addedge(i,i+x+1,0);
        else addedge(i,n+1,i+x-n);
        for(int j=i+1;j<=min(i+x+1,n)&&!pr[j];j++) pr[j] = 1 , addedge(j,j-1,1);
        for(int j=i+x+1;j<=n&&!ne[j];j++) ne[j] = 1 , addedge(j,j+1,1);
    }
    dji() , printf("%d\n",dis[n+1]);
    return 0;
}

