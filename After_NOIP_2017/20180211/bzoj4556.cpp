#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2e5+1e2,maxm=maxn*20;

char in[maxn];
int sa[maxn],rnk[maxn],tp[maxn],h[maxn];
int n;

namespace SA {
    int tax[maxn],m;
    inline void resort() {
        for(int i=0;i<=m;i++) tax[i] = 0;
        for(int i=1;i<=n;i++) tax[rnk[i]]++;
        for(int i=1;i<=m;i++) tax[i] += tax[i-1];
        for(int i=n;i;i--) sa[tax[rnk[tp[i]]]--] = tp[i];
    }
    inline bool cmp(int* sou,int x,int y,int l) {
        return sou[x] == sou[y] && sou[x+l] == sou[y+l];
    }
    inline void geth() {
        for(int i=1,k=0;i<=n;i++) {
            if( k ) --k;
            int j = sa[rnk[i]-1];
            while( in[i+k] == in[j+k] ) ++k;
            h[rnk[i]] = k;
        }
    }
    inline void getsa() {
        for(int i=1;i<=n;i++) rnk[i] = in[i] , tp[i] = i;
        m = 127 , resort();
        for(int w=1,p=0;p<n;w<<=1,m=p) {
            p = 0;
            for(int i=n-w+1;i<=n;i++) tp[++p] = i;
            for(int i=1;i<=n;i++) if( sa[i] > w ) tp[++p] = sa[i] - w;
            resort() , swap(tp,rnk) , rnk[sa[1]] = p = 1;
            for(int i=2;i<=n;i++)
                rnk[sa[i]] = cmp(tp,sa[i],sa[i-1],w) ? p : ++p;
        }
        geth();
    }
}
namespace RMQ {
    int mi[maxn][20],Log[maxn];
    
    inline void gen() {
        for(int i=2;i<=n;i++) Log[i] = Log[i>>1] + 1;
        for(int i=1;i<=n;i++) mi[i][0] = h[i];
        int L = Log[n];
        for(int l=1;l<=L;l++) {
            const int d = 1 << ( l - 1 );
            for(int i=1;i+(1<<l)-1<=n;i++) {
                mi[i][l] = min( mi[i][l-1] , mi[i+d][l-1] );
            }
        }
    }
    inline int query(int l,int r) {
        int L = Log[r-l+1];
        return min( mi[l][L] , mi[r-(1<<L)+1][L] );
    }
}

int root[maxn];

namespace CT {
    int l[maxm],r[maxm],lson[maxm],rson[maxm],sum[maxm],cnt;
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void insert(int pos,int pre,int tar) {
        l[pos] = l[pre] , r[pos] = r[pre] ,
        lson[pos] = lson[pre] , rson[pos] = rson[pre] ;
        if( l[pos] == r[pos] ) {
            sum[pos] = sum[pre] + 1;
            return;
        }
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( tar <= mid ) insert(lson[pos]=++cnt,lson[pre],tar);
        else insert(rson[pos]=++cnt,rson[pre],tar);
        sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline int query(int pos,int pre,int ll,int rr) {
        if( rr < l[pos] || r[pos] < ll ) return 0;
        if( sum[pos] == sum[pre] ) return 0;
        if( ll <= l[pos] && r[pos] <= rr ) return sum[pos] - sum[pre];
        return query(lson[pos],lson[pre],ll,rr) + query(rson[pos],rson[pre],ll,rr);
    }
}

int a,b,c,d;

inline int binl(int pos,int miv) { // return (ret,pos]
    if( RMQ::query(pos-1,pos-1) < miv ) return pos-1; // we can select nothing
    int ll = 0 , rr = pos - 1 , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( RMQ::query(mid,pos-1) < miv ) ll = mid;
        else rr = mid;
    }
    return ll;
}
inline int binr(int pos,int miv) { // return [pos,ret] .
    if( RMQ::query(pos,pos) < miv ) return pos; // we can select nothing
    int ll = pos + 1 , rr = n + 1 , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( RMQ::query(pos,mid-1) < miv ) rr = mid;
        else ll = mid; 
    }
    return ll;
}
inline bool querytree(int llim,int rlim,int l,int r) {
    return CT::query(root[rlim],root[llim],l,r);
}
inline bool judge(int len) {
    int l = binl(rnk[c],len) , r = binr(rnk[c],len);
    return !len || querytree(r,l,a,b-len+1);
}
inline int bin() {
    int ll = 0 , rr = min( b - a + 1 , d - c + 1 ) + 1 , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( judge(mid) ) ll = mid;
        else rr = mid;
    }
    return ll;
}


int main() {
    static int m;
    scanf("%d%d",&n,&m);
    scanf("%s",in+1);
    SA::getsa();
    for(int i=1;i<=n;i++) h[i] = h[i+1];
    RMQ::gen();
    CT::build(*root=CT::cnt=1,1,n);
    for(int i=1;i<=n;i++) CT::insert(root[i]=++CT::cnt,root[i-1],sa[i]);
    while( m-- ) {
        scanf("%d%d%d%d",&a,&b,&c,&d);
        printf("%d\n",bin());
    }
    return 0;
}

