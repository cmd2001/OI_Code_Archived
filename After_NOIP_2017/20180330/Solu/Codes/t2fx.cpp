#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1e4+1e2,maxe=1e5+1e2;

int ina[maxe],inb[maxe],inc[maxe],n,m;
int s[maxn],t[maxe],nxt[maxe],l[maxe],deg[maxn],d[maxn],cnt;
long double f[maxn],p[maxn],ans;

inline void addedge(int from,int to,int len) {
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt , ++deg[to];
}
inline void bfs1() {
    queue<int> q;
    for(int i=1;i<=n;i++) if( !deg[i] ) q.push(i);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at]) {
            f[t[at]] += ( f[pos] + 1 ) * l[at] / d[t[at]];
            if( !--deg[t[at]] ) q.push(t[at]);
        }
    }
}
inline void bfs2(int st) {
    queue<int> q; p[st] = 1;
    for(int i=1;i<=n;i++) if( !deg[i] ) q.push(i);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int at=s[pos];at;at=nxt[at]) {
            p[t[at]] += p[pos] * l[at] / d[pos];
            if( !--deg[t[at]] ) q.push(t[at]);
        }
    }
}
inline void getans() {
    ans = f[1];
    for(int i=1;i<=m;i++) {
        const int &a = ina[i] , &b= inb[i] , &c = inc[i];
        ans = max( ans , ( (  f[a] - ( f[b] + 1 ) * c / d[a] ) * d[a] / ( d[a] - c ) - f[a] )* p[a] + f[1] );
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) {
        scanf("%d%d%d",ina+i,inb+i,inc+i) , 
        ++ina[i] , ++inb[i] , d[ina[i]] += inc[i] , 
        addedge(inb[i],ina[i],inc[i]);
    }
    bfs1() , memset(s,0,sizeof(s)) , cnt = 0;
    for(int i=1;i<=m;i++) addedge(ina[i],inb[i],inc[i]);
    bfs2(1);
    getans();
    printf("%0.6Lf\n",ans);
    return 0;
}

