#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cctype>
using namespace std;
const int maxn=1e4+1e2,maxm=1e6+1e2,maxb=1e2+1e1;

int in[maxn],pre[maxn],srt[maxn],last[maxm];
int bel[maxn],st[maxb],ed[maxb];
int n,cnt;

inline void rebuildblk(int id) {
    for(int i=st[id];i<=ed[id];i++)
        srt[i] = pre[i];
    sort(srt+st[id],srt+ed[id]+1);
}
inline void rebuildpre() {
    for(int i=1;i<=n;i++)
        pre[i] = last[in[i]] ,
        last[in[i]] = i;
    for(int i=1;i<=cnt;i++)
        rebuildblk(i);
}
inline void update(int pos,int x) {
    for(int i=1;i<=n;i++)
        last[in[i]] = 0;
    in[pos] = x;
    rebuildpre();
}
inline int queryfull(int id,int lim) {
    return lower_bound(srt+st[id],srt+ed[id]+1,lim) - ( srt + st[id] );
}
inline int querypart(int id,int l,int r,int lim) {
    int ret = 0;
    l = max( l , st[id] ) , r = min( r , ed[id] );
    for(int i=l;i<=r;i++)
        ret += ( pre[i] < lim );
    return ret;
}
inline int query(int l,int r) {
    if( bel[l] == bel[r] )
        return querypart(bel[l],l,r,l);
    int ret = 0;
    for(int i=bel[l]+1;i<bel[r];i++)
        ret += queryfull(i,l);
    ret = ret + querypart(bel[l],l,r,l) + querypart(bel[r],l,r,l);
    return ret;
}

inline void initblk() {
    int b = sqrt(n);
    for(int l=1,r;l<=n;l=r+1) {
        r = min( l + b - 1 , n ) , ++cnt;
        st[cnt] = l , ed[cnt] = r;
        for(int i=l;i<=r;i++)
            bel[i] = cnt;
    }
}

inline char nextchar() {
    #define BUFSIZE (1<<14)
    static char buf[BUFSIZE],*st=buf+BUFSIZE,*ed=buf+BUFSIZE;
    if( st == ed ) ed = buf + fread( st = buf , 1 , BUFSIZE , stdin );
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch ;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}
inline char realchar() {
    char ret;
    while( !isalpha(ret=nextchar()) );
    return ret;
}
int main() {
    static int m;
    n = getint() , m = getint();
    for(int i=1;i<=n;i++)
        in[i] = getint();
    initblk();
    rebuildpre();
    for(int i=1,c,l,r,pos,x;i<=m;i++) {
        c = realchar();
        if( c == 'Q' ) {
            l = getint() , r = getint();
            printf("%d\n",query(l,r));
        } else if( c == 'R' ) {
            pos = getint() , x = getint();
            update(pos,x);
        }
    }
    return 0;
}
