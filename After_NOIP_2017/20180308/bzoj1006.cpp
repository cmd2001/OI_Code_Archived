#include<cstdio>
#include<algorithm>
const int maxn=1e4+1e2,maxe=1e6+1e2;

int s[maxn],t[maxe<<1],nxt[maxe<<1];
int col[maxn],del[maxn],deg[maxn],q[maxn],lst[maxn],ans;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d",&a,&b) , 
        addedge(a,b) , addedge(b,a);
    }
    *deg = -1;
    for(int i=n;i;i--) {
        int j = 0;
        for(int k=1;k<=n;k++) if( !del[k] && deg[k] >= deg[j] ) j = k;
        q[i] = j , del[j] = 1;
        for(int at=s[j];at;at=nxt[at]) if( !del[t[at]] ) ++deg[t[at]];
    }
    for(int i=n;i;i--) {
        for(int at=s[q[i]];at;at=nxt[at]) lst[col[t[at]]] = i;
        for(col[q[i]]=1;lst[col[q[i]]]==i;col[q[i]]++) ;
        ans = std::max( ans , col[q[i]] );
    }
    printf("%d\n",ans);
    return 0;
}
