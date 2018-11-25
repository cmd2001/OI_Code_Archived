#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=3e4+1e2;

struct BinaryIndexTree {
    int dat[maxn],siz;
    
    #define lowbit(x) (x&-x)
    
    inline void update(int pos,int x) {
        while( pos <= siz )
            dat[pos] += x , pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while( pos )
            ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
    inline void resize(int ss) {
        siz = ss;
    }
}bit;

struct QNode {
    int tpe; // tpe == 1 means query , 0 means change
    int pos,val,del;
    int st,ed,k,qid;
}ns[maxn],tp[2][maxn];

int in[maxn],srt[maxn],ans[maxn],len;

inline void solve(int ql,int qr,int al,int ar) {
    //debug<<"ql = "<<ql<<"qr = "<<ar<<"al = "<<al<<"ar = "<<ar<<endl;
    if( al == ar ) {
        for(int i=ql;i<=qr;i++)
            if( ns[i].tpe )
                ans[ns[i].qid] = al;
        return;
    }
    const int amid = ( al + ar ) >> 1;
    //debug<<"mid = "<<amid<<endl;
    int cntl = 0 , cntr = 0;
    for(int i=ql;i<=qr;i++) {
        if( ns[i].tpe ) {
            const int kk = bit.query(ns[i].ed) - bit.query(ns[i].st-1);
            if( ns[i].k > kk ) {
                //debug<<"kk = "<<kk<<endl;
                ns[i].k -= kk ,
                tp[1][++cntr] = ns[i];
            } else tp[0][++cntl] = ns[i];
        } else {
            if( ns[i].val <= amid ) {
                //debug<<"val = "<<ns[i].val<<"del = "<<ns[i].del<<endl;
                bit.update(ns[i].pos,ns[i].del);
                tp[0][++cntl] = ns[i];
            } else tp[1][++cntr] = ns[i];
        }
    }
    for(int i=ql;i<=qr;i++)
        if( !ns[i].tpe && ns[i].val <= amid )
            bit.update(ns[i].pos,-ns[i].del);
    const int qmid = ql + cntl - 1;
    memcpy(ns+ql,tp[0]+1,sizeof(tp[0][0])*cntl);
    memcpy(ns+qmid+1,tp[1]+1,sizeof(tp[1][0])*cntr);
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
    static int n,m,cnt,qcnt;
    static char com[10];
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) {
        ns[++cnt].val = in[i] = srt[++len] = getint() ,
        ns[cnt].pos = i;ns[cnt].del = 1;
    }
    for(int i=1,p;i<=m;i++) {
        scanf("%s",com);
        if( *com == 'Q' ) {
            ns[++cnt].tpe = 1 , ns[cnt].qid = ++qcnt;
            ns[cnt].st = getint() , ns[cnt].ed = getint() , ns[cnt].k = getint();
        } else {
            p = getint();
            ns[++cnt].pos = p , ns[cnt].val = in[p] , ns[cnt].del = -1;
            ns[++cnt].pos = p , srt[++len] = ns[cnt].val = in[p] = getint() , ns[cnt].del = 1;
        }
    }
    sort(srt+1,srt+1+len) , len = unique(srt+1,srt+1+len) - srt - 1;
    for(int i=1;i<=cnt;i++)
        if( !ns[i].tpe ) {
            ns[i].val = lower_bound(srt+1,srt+1+len,ns[i].val) - srt;
        }
    
    bit.resize(n);
    solve(1,cnt,1,len);
    
    for(int i=1;i<=qcnt;i++)
        printf("%d\n",srt[ans[i]]);
    
    return 0;
}

