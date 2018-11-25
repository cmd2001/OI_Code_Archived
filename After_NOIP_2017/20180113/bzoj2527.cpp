#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=3e5+1e2;
const int inf=0x3f3f3f3f;

struct BinaryIndexTree {
    lli org[maxn],del[maxn];
    int siz;
    #define lowbit(x) (x&-x)
    inline void cup(lli* dst,int pos,lli x) {
        while( pos <= siz )
            dst[pos] += x ,
            pos += lowbit(pos);
    }
    inline lli cqr(lli *sou,int pos) {
        lli ret = 0;
        while( pos )
            ret += sou[pos] ,
            pos -= lowbit(pos);
        return ret;
    }
    inline lli qrp(int pos) {
        return cqr(org,pos) + cqr(del,pos) * pos;
    }
    inline void update(int st,int ed,lli x) {
        cup(org,st,-(st-1)*x); cup(org,ed,ed*x);
        cup(del,st,x); cup(del,ed,-x);
    }
    inline lli query(int st,int ed) {
        return qrp(ed) - qrp(st-1);
    }
    inline void resize(int ss) {
        siz = ss;
    }
}bit;

int ans[maxn],con[maxn],tp[2][maxn];
int l[maxn],r[maxn],a[maxn],tar[maxn];
vector<int> hve[maxn];
int n,m,k; // n is size of countries , m is size of stations .
//Meaningless life ! rm -rf ME

inline lli sumc(int pos) {
    lli ret = 0;;
    for(unsigned i=0;i<hve[pos].size();i++) {
        ret += bit.query(hve[pos][i],hve[pos][i]);
        if( ret > tar[pos] )
            break;
    }
    return ret;
}
inline void operate(int l,int r,lli a) {
    if( l <= r ) {
        bit.update(l,r,a);
    } else {
        bit.update(l,m,a);
        bit.update(1,r,a);
    }
}
inline void solve(int cl,int cr,int ql,int qr) {
    if( ql == qr ) {
        for(int i=cl;i<=cr;i++)
            ans[con[i]] = ql;
        return;
    }
    const int qmid = ( ql + qr ) >> 1;
    int cnt0=0,cnt1=0;
    for(int i=ql;i<=qmid;i++)
        operate(l[i],r[i],a[i]);
    for(int i=cl;i<=cr;i++) {
        lli now = sumc(con[i]);
        if( tar[con[i]] <= now ) {
            tp[0][++cnt0] = con[i];
        } else {
            tp[1][++cnt1] = con[i];
            tar[con[i]] -= now;
        }
    }
    for(int i=ql;i<=qmid;i++)
        operate(l[i],r[i],-a[i]);
    const int cmid = cl + cnt0 - 1;
    int lp = cl , rp = cmid + 1;
    for(int i=1;i<=cnt0;i++)
        con[lp++] = tp[0][i];
    for(int i=1;i<=cnt1;i++)
        con[rp++] = tp[1][i];
    solve(cl,cmid,ql,qmid);
    solve(cmid+1,cr,qmid+1,qr);
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1,t;i<=m;i++) {
        scanf("%d",&t);
        hve[t].push_back(i);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",tar+i);
    scanf("%d",&k);
    for(int i=1;i<=k;i++)
        scanf("%d%d%d",l+i,r+i,a+i);
    
    ++k , l[k] = 1 , r[k] = m , a[k] = inf;
    bit.resize(m);
    for(int i=1;i<=n;i++)
        con[i] = i;
    
    solve(1,n,1,k);
    
    for(int i=1;i<=n;i++)
        if( ans[i] != k ) printf("%d\n",ans[i]);
        else puts("NIE");
    
    return 0;
}
