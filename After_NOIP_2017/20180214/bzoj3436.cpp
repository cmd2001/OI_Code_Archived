#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e4+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1],dis[maxn];
bool vis[maxn],fail;

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void spfa(int pos) {
    if( vis[pos] ) {
        fail = 1;
        return;
    }
    vis[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( dis[t[at]] > dis[pos] + l[at] ) {
            dis[t[at]] = dis[pos] + l[at];
            spfa(t[at]);
            if( fail ) return;
        }
    vis[pos] = 0;
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,ope,x,y,v;i<=m;i++) {
        scanf("%d%d%d",&ope,&x,&y);
        if( ope == 3 ) addedge(x,y,0) , addedge(y,x,0);
        else {
            scanf("%d",&v);
            if( ope == 1 ) addedge(x,y,-v);
            else addedge(y,x,v);
        }
    }
    for(int i=1;i<=n&&!fail;i++) {
        dis[i] = 0;
        spfa(i);
    }
    puts(fail?"No":"Yes");
    return 0;
}
