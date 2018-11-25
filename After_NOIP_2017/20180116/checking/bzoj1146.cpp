#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=8e4+1e2;

struct InNode {
    int val,pos;
    friend bool operator < (const InNode &a,const InNode &b) {
        return a.val < b.val;
    }
}is[maxn],itp[2][maxn];
struct QNode {
    int a,b,k,id;
}qs[maxn],qtp[2][maxn];

int srt[maxn],ans[maxn],len;
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],top[maxn],dep[maxn],siz[maxn],son[maxn],num[maxn],cov[maxn];
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],sum[maxn<<3],cnt;

inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) return;
    const int mid = ( ll + rr ) >> 1;
    build(lson[pos]=++cnt,ll,mid);
    build(rson[pos]=++cnt,mid+1,rr);
}
inline void update(int pos,int tar,int x) {
    if( tar < l[pos] || r[pos] < tar ) return;
    if( l[pos] == r[pos] && l[pos] == tar ) {
        sum[pos] += x;
        return;
    }
    update(lson[pos],tar,x);
    update(rson[pos],tar,x);
    sum[pos] = sum[lson[pos]] + sum[rson[pos]];
}
inline int query(int pos,int ll,int rr) {
    if( rr < l[pos] || r[pos] < ll ) return 0;
    if( ll <= l[pos] || r[pos] <= rr ) return sum[pos];
    return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
}

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] ) {
            fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1;
            pre(t[at]);
            siz[pos] += siz[t[at]];
            son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
        }
}
inline void dfs(int pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    num[pos] = pos == son[fa[pos]] ? num[fa[pos]] + 1 : 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] )
            dfs(t[at]);
    if( !son[pos] )
        build(cov[top[pos]]=++cnt,num[top[pos]],num[pos]);
}
inline int chain(int a,int b) {
    int ret = 0;
    while( top[a] != top[b] ) {
        if( dep[top[a]] > dep[top[b]] ) {
            ret += query(cov[top[a]],num[top[a]],num[a]);
            a = fa[top[a]];
        } else {
            ret += query(cov[top[b]],num[top[b]],num[b]);
            b = fa[top[b]];
        }
    }
    ret += query(cov[top[a]],min(num[a],num[b]),max(num[a],num[b]));
    return ret;
}

inline void solve(int ql,int qr,int il,int ir,int al,int ar) {
    if( al == ar ) {
        for(int i=ql;i<=qr;i++)
            ans[qs[i].id] = al;
        return;
    }
    const int amid = ( al + ar ) >> 1;
    for(int i=il;i<=ir;i++)
        if( is[i].val <= amid ) {
            const int pos = is[i].pos;
            update(cov[top[pos]],num[pos],1);
        }
    int qcntl = 0 , qcntr = 0;
    for(int i=ql;i<=qr;i++) {
        int jud = chain( qs[i].a , qs[i].b );
        if( jud >= qs[i].k ) {
            qtp[0][++qcntl] = qs[i];
        } else {
            qs[i].k -= jud , qtp[1][++qcntr] = qs[i];
        }
    }
    int icntl = 0 , icntr = 0;
    for(int i=il;i<=ir;i++) {
        if( is[i].val <= amid ) {
            const int pos = is[i].pos;
            update(cov[top[pos]],num[pos],-1);
            itp[0][++icntl] = is[i];
        }
        else itp[1][++icntr] = is[i];
    }
    const int qmid = ql + qcntl - 1 , imid = il + icntl - 1;
    
    memcpy( qs + ql , qtp[0] + 1 , sizeof(qtp[0][0]) * qcntl );
    memcpy( qs + qmid + 1 , qtp[1] + 1 , sizeof(qtp[1][0]) * qcntr );
    memcpy( is + il , itp[0] + 1 , sizeof(itp[0][0]) * icntl );
    memcpy( is + imid + 1 , itp[1] + 1 , sizeof(itp[1][0]) * icntr );
    
    solve(ql,qmid,il,imid,al,amid);
    solve(qmid+1,qr,imid+1,ir,amid+1,ar);
    
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int n,m;
    n = getint() , m = getint();
    for(int i=1;i<=n;i++)
        srt[i] = is[i].val = getint() , is[i].pos = i;
    for(int i=1,a,b;i<n;i++) {
        a = getint() , b = getint();
        addedge(a,b); addedge(b,a);
    }
    
}
