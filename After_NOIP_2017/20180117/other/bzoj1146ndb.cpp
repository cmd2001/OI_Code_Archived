#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cerr
using namespace std;
const int maxn=8e4+1e2;

struct QNode {
    int tpe; // 1 means query , 0 means change
    int k,a,b,qid;
    int pos,val,add;
}ns[maxn<<2],tp[2][maxn<<2];

int in[maxn],srt[maxn<<1],ans[maxn],len;
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],num[maxn],cov[maxn];
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],su[maxn<<3],cnt;
int n,m;

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
        su[pos] += x;
        return;
    }
    update(lson[pos],tar,x);
    update(rson[pos],tar,x);
    su[pos] = su[lson[pos]] + su[rson[pos]];
}
inline int query(int pos,int ll,int rr) {
    if( rr < l[pos] || r[pos] < ll ) return 0;
    if( ll <= l[pos] && r[pos] <= rr ) return su[pos];
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
            ret += query(cov[top[a]],num[top[a]],num[a]),
            a = fa[top[a]];
        } else {
            ret += query(cov[top[b]],num[top[b]],num[b]),
            b = fa[top[b]];
        }
    }
    ret += query(cov[top[a]],min(num[a],num[b]),max(num[a],num[b]));
    return ret;
}

inline void solve(int ql,int qr,int al,int ar) {
    if( al == ar ) {
        for(int i=ql;i<=qr;i++)
            if( ns[i].tpe )
                ans[ns[i].qid] = al;
        return;
    }
    const int amid = ( al + ar ) >> 1;
    int cntl = 0 , cntr = 0;
    for(int i=ql;i<=qr;i++) {
        if( ns[i].tpe ) {
            int kk = chain(ns[i].a,ns[i].b);
            if( ns[i].k > kk ) {
                ns[i].k -= kk , tp[0][++cntl] = ns[i];
            } else tp[1][++cntr] = ns[i];
        } else {
            if( ns[i].val > amid ) {
                const int &pos = ns[i].pos;
                update(cov[top[pos]],num[pos],ns[i].add);
                tp[1][++cntr] = ns[i];
            } else tp[0][++cntl] = ns[i];
        }
    }
    for(int i=qr;i>=ql;i--)
        if( ns[i].val > amid ) {
            const int &pos = ns[i].pos;
            update(cov[top[pos]],num[pos],-ns[i].add);
        }
    const int qmid = ql + cntl - 1;
    
    memcpy( ns + ql , tp[0] + 1 , sizeof(tp[0][0]) * cntl );
    memcpy( ns + qmid + 1 , tp[1] + 1 , sizeof(tp[1][1]) * cntr );
    
    solve(ql,qmid,al,amid);
    solve(qmid+1,qr,amid+1,ar);
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int qcnt,qlen;
    n = getint() , m = getint();
    qlen = n;
    for(int i=1;i<=n;i++)
        ns[i].pos = i , in[i] = ns[i].val = srt[++len] = getint() , ns[i].add = 1;
    for(int i=1,a,b;i<n;i++) {
        a = getint() , b = getint();
        addedge(a,b) , addedge(b,a);
    }
    for(int i=1,k,p;i<=m;i++) {
        k = getint();
        if( !k ) {
            p = getint();
            ++qlen , ns[qlen].pos = p , ns[qlen].val = in[p] , ns[qlen].add = -1;
            ++qlen , ns[qlen].pos = p , in[p] = ns[qlen].val = srt[++len] = getint() , ns[qlen].add = 1;
        } else {
            ++qlen , ns[qlen].tpe = 1 , ns[qlen].a = getint() , ns[qlen].b = getint() , ns[qlen].k = k , ns[qlen].qid = ++qcnt;
        }
    }
    
    sort(srt+1,srt+1+len);
    len = unique(srt+1,srt+1+len) - srt - 1;
    for(int i=1;i<=qlen;i++)
        if( ! ns[i].tpe ) ns[i].val = lower_bound(srt+1,srt+1+len,ns[i].val) - srt;
    
    pre(1);dfs(1);
    solve(1,qlen,0,len);
    
    for(int i=1;i<=qcnt;i++)
        if( ans[i] ) printf("%d\n",srt[ans[i]]);
        else puts("invalid request!");
    
    return 0;
}