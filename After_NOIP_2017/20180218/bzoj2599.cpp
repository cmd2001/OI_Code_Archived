#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
const int maxn=2e5+1e2,maxk=1e6+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
int tax[maxk];
int dis[maxn],used[maxn],bel[maxn],cnt;
bool del[maxn];
int siz[maxn],mxs[maxn],sum,root,ans; // set *mxs = inf and root = 0 .
int k;
int rel = 0;

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void prefindroot(int pos,int fa) {
    siz[pos] = 1 , ++sum;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !del[t[at]] ) {
        prefindroot(t[at],pos);
        siz[pos] += siz[t[at]];
    }
}
inline void findroot(int pos,int fa) {
    mxs[pos] = ~fa ? sum - siz[pos] : 0;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !del[t[at]] ) {
        findroot(t[at],pos);
        mxs[pos] = max( mxs[pos] , siz[t[at]] );
    }
    if( mxs[pos] < mxs[root] ) root = pos;
}
inline void getdis(int pos,int fa,int dd,int uu,int bb) {
    ++rel;
    if( dd > k || uu > ans ) return; // this dfs is useless .
    dis[++cnt] = dd , used[cnt] = uu , bel[cnt] = bb;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !del[t[at]] )
        getdis(t[at],pos,dd+l[at],uu+1,bb);
}
inline void calc() {
    for(int l=1,r;l<=cnt;l=r+1) {
        r = l;
        while( r<cnt && bel[r+1] == bel[l] ) ++r;
        for(int i=l;i<=r;i++) ans = min( ans , used[i] + tax[k-dis[i]] );
        for(int i=l;i<=r;i++) tax[dis[i]] = min( tax[dis[i]] , used[i] );
    }
    ans = min( ans , tax[k] );
    for(int i=1;i<=cnt;i++) tax[dis[i]] = inf;
}
inline void work(int pos) {
    mxs[root=0] = inf , sum = 0;
    prefindroot(pos,-1) , findroot(pos,-1);
    const int rt = root; del[rt] = 1 , cnt = 0;
    for(int at=s[rt];at;at=nxt[at])
        if( !del[t[at]] ) getdis(t[at],-1,l[at],1,t[at]);
    calc();
    for(int at=s[rt];at;at=nxt[at])
        if( !del[t[at]] ) work(t[at]);
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int n;
    memset(tax,0x3f,sizeof(tax));
    n = getint() , k = getint();
    for(int i=1,a,b,l;i<n;i++) {
        a = getint() + 1 , b = getint() + 1 , l = getint();
        addedge(a,b,l) , addedge(b,a,l);
    }
    ans = inf;
    work(1);
    printf("%d\n",ans!=inf?ans:-1);
    return 0;
}
