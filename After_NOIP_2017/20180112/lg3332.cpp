#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e4+1e2;

struct BinaryIndexTree {
    lli org[maxn],del[maxn];
    int siz;
    #define lowbit(x) (x&-x)
    
    inline void cupd(lli* dst,int pos,int add) {
        while( pos <= siz )
            dst[pos] += add , pos += lowbit(pos);
    }
    inline lli cqry(lli* sou,int pos) {
        lli ret = 0;
        while( pos )
            ret += sou[pos] , pos -= lowbit(pos);
        return ret;
    }
    inline lli qryp(int pos) {
        return cqry(org,pos) + cqry(del,pos) * pos;
    }
    inline void update(int l,int r,int add) {
        cupd(org,l,-(l-1)*add);
        cupd(org,r,r*add);
        cupd(del,l,add);
        cupd(del,r,-add);
    }
    inline lli query(int l,int r) {
        return qryp(r) - qryp(l-1);
    }
    inline void resize(int ss) {
        siz = ss;
    }
}bit;

int ans[maxn];

struct QNode { // type == 1 means update , type == 2 means query;
    int tpe,l,r,x,qid;
    lli k;
}ns[maxn],tpl[maxn],tpr[maxn];

inline void solve(int ql,int qr,int al,int ar) {
    //debug<<"ql = "<<ql<<"qr = "<<qr<<"al = "<<al<<"ar = "<<ar<<endl;
    if( al == ar ) {
        for(int i=ql;i<=qr;i++)
            if( ns[i].tpe == 2 ) {
                ans[ns[i].qid] = al;
                //debug<<"al = "<<al<<endl;
            }
        return;
    }
    const int amid = ( al + ar ) >> 1;
    int cntl = 0 , cntr = 0;
    for(int i=ql;i<=qr;i++) {
        if( ns[i].tpe == 1 ) {
            if( ns[i].x <= amid ) {
                tpl[++cntl] = ns[i];
            } else {
                bit.update(ns[i].l,ns[i].r,1);
                tpr[++cntr] = ns[i];
            }
        }
        else {
            lli lam = bit.query(ns[i].l,ns[i].r);
            //debug<<"i = "<<i<<"l = "<<ns[i].l<<"r = "<<ns[i].r<<endl;
            //debug<<"lam = "<<lam<<endl;
            if( ns[i].k <= lam ) {
                tpr[++cntr] = ns[i];
            } else {
                //debug<<"to left"<<endl;
                ns[i].k -= lam;
                tpl[++cntl] = ns[i];
            }
        }
    }
    for(int i=1;i<=cntr;i++)
        if( tpr[i].tpe == 1 )
            bit.update(tpr[i].l,tpr[i].r,-1);
    
    const int qmid = ql + cntl - 1;
    int c1 = ql , c2 = qmid + 1;
    for(int i=1;i<=cntl;i++)
        ns[c1++] = tpl[i];
    for(int i=1;i<=cntr;i++)
        ns[c2++] = tpr[i];
    
    solve(ql,qmid,al,amid);
    solve(qmid+1,qr,amid+1,ar);
}

inline int getint() {
    int ret = 0 , ch ;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
signed main() {
    static int n,m,qid;
    n = getint() , m = getint();
    bit.resize(n);
    for(int i=1;i<=m;i++) {
        ns[i].tpe = getint() , ns[i].l = getint() , ns[i].r = getint();
        if( ns[i].tpe == 1 ) {
            scanf("%d",&ns[i].x);
        } else {
            scanf("%lld",&ns[i].k);
            ns[i].qid = ++qid;
        }
    }
    
    //for(int i=1;i<=m;i++) debug<<ns[i].l<<" "<<ns[i].r<<endl;
    
    solve(1,m,-n,n);
    
    for(int i=1;i<=qid;i++)
        printf("%d\n",ans[i]);
    
    return 0;
}

