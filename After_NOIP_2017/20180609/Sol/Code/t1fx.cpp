#include<cstdio>
const int maxn=3e4+1e2,maxe=1e5+1e2;

int s[maxn],t[maxe<<1],nxt[maxe<<1],l[maxe<<1],su,n;

inline void addedge(int from,int to,int lim) {
    static int cnt;
    t[++cnt] = to , l[cnt] = lim , nxt[cnt] = s[from] , s[from] = cnt;
    if( from == n ) su += lim;
}

inline void dfs(int pos) {
    for(int &at=s[pos];at;at=nxt[at]) if( l[at]-- ) dfs(t[at]) , printf("%d%c",pos,pos!=n?' ':'\n');
}

int main() {
    static int m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b,l;i<=m;i++) scanf("%d%d%d",&a,&b,&l) , addedge(b,a,l);
    addedge(1,n,su) , dfs(n);
    return 0;
}
