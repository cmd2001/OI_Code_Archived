#include<cstdio>
const int maxn=1e5+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
int d[maxn],p[maxn],ans,mx,ax,ay;

inline void addedge(int from,int to,int len) {
    static int cnt = 1;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos,int fa) {
    d[pos] = 0 , p[pos] = pos;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
        dfs(t[at],pos);
        if( d[pos] + d[t[at]] + l[at] > mx ) mx = d[pos] + d[t[at]] + l[at] , ax = p[pos] , ay = p[t[at]];
        if( d[t[at]] + l[at] > d[pos] ) d[pos] = d[t[at]] + l[at] , p[pos] = p[t[at]];
    }
}
inline bool rel(int pos,int fa,int tar) {
    if( pos == tar ) return 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && rel(t[at],pos,tar) ) return l[at] = -l[at] , l[at^1] = -l[at^1] , 1;
    return 0;
}

int main() {
    static int n,k;
    scanf("%d%d",&n,&k) , ans = n - 1 << 1;
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b,1) , addedge(b,a,1);
    while(k--) mx = ax = ay = 0 , dfs(1,-1) , rel(ax,-1,ay) , ans -= mx - 1;
    printf("%d\n",ans);
    return 0;
}
