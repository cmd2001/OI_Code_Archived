#pragma GCC optimize(3)
#include<cstdio>
#include<algorithm>
using std::max;
using std::sort;
using std::unique;
using std::lower_bound;
const int maxn=8e5+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int l[maxn],r[maxn],f[maxn],ans[maxn],mia;
int srt[maxn],len;
int stk[maxn],top;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos) {
    stk[++top] = pos;
    if( pos <= len ) 
        for( ans[pos] = mia ; stk[top-ans[pos]] < pos + len ; ans[pos] ++ ) ;
    for(int at=s[pos];at;at=nxt[at])
        dfs(t[at]);
    stk[top--] = 0;
}
int main() {
    int n;
    scanf("%d%d",&n,srt+(len=1));
    for(int i=1;i<=n;i++) {
        scanf("%d%d",l+i,r+i) ,
        srt[++len] = l[i] , srt[++len] = r[i];
    }
    sort(srt+1,srt+1+len) , len = unique(srt+1,srt+1+len) - srt - 1;
    for(int i=1;i<=n;i++)
        l[i] = lower_bound(srt+1,srt+1+len,l[i]) - srt ,
        r[i] = lower_bound(srt+1,srt+1+len,r[i]) - srt ;
    for(int i=1;i<=n;i++)
        if( l[i] <= r[i] ) {
            f[l[i]] = max( f[l[i]] , r[i] ) ,
            f[l[i]+len] = max( f[l[i]+len] , r[i]+len );
        } else {
            f[1] = max( f[1] , r[i] ) ,
            f[l[i]] = max( f[l[i]] , r[i] + len ) ,
            f[l[i]+len] = max( f[l[i]+len] , len<<1 );
        }
    for(int i=2;i<=len<<1;i++)
        f[i] = max( f[i] , f[i-1] );
    for(int i=1;i<len<<1;i++)
        addedge(f[i],i);
    mia = -1;
    for(int i=1;i<len;i=f[i]) ++mia;
    dfs(len<<1);
    for(int i=1;i<=n;i++)
        printf("%d ",ans[l[i]]);
    putchar('\n');
    return 0;
}
