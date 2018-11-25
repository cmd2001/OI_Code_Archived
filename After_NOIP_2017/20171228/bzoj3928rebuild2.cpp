%:pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxq=6e5+1e2;
 
lli srt[maxq];
 
inline lli f(const lli &k,const lli &b,const int &x) {
    return k * srt[x] + b;
}

int lson[maxq<<3],rson[maxq<<3];
struct SegmentTree {
    int cnt;
    lli k[maxq<<3],b[maxq<<3];
     
    inline void build(int pos,int ll,int rr) {
        if( ll == rr )
            return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid);
        build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void update(int pos,int l,int r,int ll,int rr,lli kk,lli bb) {
        if( rr < l || r < ll )
            return;
        const int mid = ( l + r ) >> 1;
        if( ll <= l && r <= rr ) {
            if( f(kk,bb,l) <= f(k[pos],b[pos],l) && f(kk,bb,r) <= f(k[pos],b[pos],r) )
                return;
            if( l == r ) {
            	k[pos] = kk , b[pos] = bb;
            	return;
            }
            if( kk > k[pos] ) {
                if( f(kk,bb,mid) > f(k[pos],b[pos],mid) ) {
                    update(lson[pos],l,mid,l,r,k[pos],b[pos]);
                    k[pos] = kk , b[pos] = bb;
                }
                else
                    update(rson[pos],mid+1,r,ll,rr,kk,bb);
            }
            else {
                if( f(kk,bb,mid) > f(k[pos],b[pos],mid) ) {
                    update(rson[pos],mid+1,r,l,r,k[pos],b[pos]);
                    k[pos] = kk , b[pos] = bb;
                }
                else
                    update(lson[pos],l,mid,ll,rr,kk,bb);
            }
        }
        update(lson[pos],l,mid,ll,rr,kk,bb);
        update(rson[pos],mid+1,r,ll,rr,kk,bb);
    }
    inline lli query(int pos,int l,int r,int tar) {
        lli ret = f(k[pos],b[pos],tar);
        if( l == r )
            return ret;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid )
            ret = max( ret , query(lson[pos],l,mid,tar) );
        else
            ret = max( ret , query(rson[pos],mid+1,r,tar) );
        return ret;
    }
}up,down;
 
int s[maxn],st[maxq],ed[maxq];
lli k[maxq],b[maxq];
int ope[maxq][4];
int n,m,len=1,cnt;
int v[maxn];
 
inline lli getb(int pos,int tme,lli newk) {
    lli alpha = f(k[pos],b[pos],tme);
    return alpha - newk * srt[tme];
}
inline void add(int pos,int tt,lli kk,lli bb=0) {
    k[++cnt] = kk;
    if( !bb )
        bb = getb(s[pos],tt,kk);
    b[cnt] = bb;
    st[cnt] = tt , ed[cnt] = len;
    if( s[pos] )
        ed[s[pos]] = tt;
    s[pos] = cnt;
}
 
inline void init() {
    sort(srt+1,srt+1+len);
    len = unique(srt+1,srt+1+len) - srt - 1;
    for(int i=1;i<=m;i++)
        ope[i][1] = lower_bound(srt+1,srt+1+len,ope[i][1]) - srt;
    for(int i=1;i<=n;i++)
    	add(i,0,0,v[i]);
    for(int i=1;i<=m;i++)
        if( *ope[i] ) {
            add(ope[i][2],ope[i][1],ope[i][3]);
        }
     
    up.build(up.cnt=1,1,len);
     
    for(int i=1;i<=cnt;i++) {
        up.update(1,1,len,st[i],ed[i],k[i],b[i]);
		down.update(1,1,len,st[i],ed[i],-k[i],-b[i]);
    }
}
 
inline void work() {
    static lli ans;
    for(int i=1;i<=m;i++)
        if( ! *ope[i] ) {
            ans = max( up.query(1,1,len,ope[i][1]) , down.query(1,1,len,ope[i][1]) );
            printf("%lld\n",ans);
        }
}

inline int getint() {
    int ret = 0 , fix = 1;
    char ch = getchar();
    while( !isdigit(ch) )
        fix = ch == '-' ? -1 : fix,
        ch = getchar();
    while( isdigit(ch) )
        ret = ret * 10 + ch - '0',
        ch = getchar();
    return ret * fix;
}
int main() {
    static char com[20];
    //scanf("%d%d",&n,&m);
    n = getint() , m = getint();
    for(int i=1;i<=n;i++)
        //scanf("%d",v+i);
        v[i] = getint();
    for(int i=1;i<=m;i++) {
        //scanf("%d",&ope[i][1]);
        ope[i][1] = getint();
        srt[++len] = ope[i][1];
        scanf("%s",com);
        if( *com == 'c' ) {
            ope[i][0] = 1;
            //scanf("%d%d",&ope[i][2],&ope[i][3]);
            ope[i][2] = getint() , ope[i][3] = getint();
        }
    }
    init();
    work();
     
    return 0;
}
