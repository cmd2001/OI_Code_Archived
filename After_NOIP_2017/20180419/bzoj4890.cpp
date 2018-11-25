#include<cstdio>
#include<algorithm>
const int maxn=5e3+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1],ban[maxn<<1];
int mxlen[maxn],seclen[maxn],son[maxn],del[maxn],curmx;
int x[maxn],y[maxn],len[maxn];

inline void coredge(int from,int to,int len) {
    static int cnt = 1;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int a,int b,int len) {
    coredge(a,b,len) , coredge(b,a,len);
}
inline void dfs1(int pos,int fa) {
    mxlen[pos] = seclen[pos] = son[pos] = 0;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[at] ) {
        dfs1(t[at],pos) , curmx = std::max( curmx , mxlen[pos] + mxlen[t[at]] + l[at] );
        if( mxlen[t[at]] + l[at] > mxlen[pos] ) seclen[pos] = mxlen[pos] , mxlen[pos] = mxlen[t[at]] + l[at] , son[pos] = t[at];
        else if( mxlen[t[at]] + l[at] > seclen[pos] ) seclen[pos] = mxlen[t[at]] + l[at];
    }
}
inline int dfs2(int pos,int fa,int distofa) {
    int ret = std::max( distofa , mxlen[pos] );
    for(int at=s[pos],distoson;at;at=nxt[at]) if( t[at] != fa && !ban[at] ) {
        if( t[at] != son[pos] ) distoson = std::max( distofa , mxlen[pos] ) + l[at];
        else distoson = std::max( distofa , seclen[pos] ) + l[at];
        ret = std::min( ret , dfs2(t[at],pos,distoson) );
    }
    return ret;
}

inline int solve(int id) {
    ban[id<<1] = ban[id<<1|1] = 1;
    int ret = 0;
    curmx = 0 , dfs1(x[id],-1) , ret = std::max( ret , curmx ) ,
    curmx = 0 , dfs1(y[id],-1) , ret = std::max( ret , curmx ) ,
    ret = std::max( ret , dfs2(x[id],-1,0) + dfs2(y[id],-1,0) + len[id] );
    ban[id<<1] = ban[id<<1|1] = 0;
    return ret;
}

int main() {
    static int n , ans = inf;
    scanf("%d",&n);
    for(int i=1;i<n;i++) scanf("%d%d%d",x+i,y+i,len+i) , doubledge(x[i],y[i],len[i]);
    for(int i=1;i<n;i++) ans = std::min( ans , solve(i) );
    printf("%d\n",ans);
    return 0;
}

