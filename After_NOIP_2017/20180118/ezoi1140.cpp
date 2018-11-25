#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e5+1e2,maxm=5e5+1e2;

int bel[maxn];

struct Edge {
    int a,b,len;
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.len < b.len;
    }
}ns[maxm];

int n,m,q;

inline int getedge(int x,int y) {
    for(int i=1;i<=m;i++)
        if( ( bel[ns[i].a] == x && bel[ns[i].b] == y ) || ( bel[ns[i].a] == y && bel[ns[i].b] == x ) ) {
            return ns[i].len;
        }
    return -1;
}

int main() {
    freopen("dat.txt","r",stdin);
    freopen("tle.txt","w",stdout);
    static char com[10];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&ns[i].a,&ns[i].b,&ns[i].len);
    for(int i=1;i<=n;i++)
        bel[i] = 1;
    sort(ns+1,ns+1+m);
    scanf("%d",&q);
    while( q-- ) {
        scanf("%s",com);
        if( *com == 'A' ) {
            int ans = getedge(com[3]-'A'+1,com[4]-'A'+1);
            if( !~ans ) puts("No Found!");
            else printf("%d\n",ans);
        } else {
            int x;
            scanf("%d",&x);
            bel[x] = com[4] - 'A' + 1 ;
        }
    }
    return 0;
}