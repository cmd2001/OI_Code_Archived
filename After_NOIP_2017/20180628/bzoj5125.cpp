#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
typedef unsigned int uint;
using namespace std;
const int maxn=4e4+1e2,maxk=13,maxb=2e2+1e1,bs=2e2;

inline int* NewArray() {
    static int pool[maxn][maxb],cnt;
    return pool[cnt++];
}

struct PersistentBlockedArray {
    int *sou[maxb],sum[maxb];
    inline void update(int pos) {
        const int bel = pos / bs , bid = pos % bs;
        int* t = NewArray();
        if( sou[bel] ) memcpy(t,sou[bel],sizeof(int)*maxb);
        sou[bel] = t;
        for(int i=bid;i<=bs;i++) ++t[i];
        for(int i=bel+1;i<=bs;i++) ++sum[i];
    }
    inline int query(int pos) {
        const int bel = pos / bs , bid = pos % bs;
        if( !sou[bel] ) return sum[bel]; 
        return sou[bel][bid] + sum[bel];
    }
}pba[maxn];

int in[maxn];
uint f[2][maxn],t;
int l=1,r=1;

inline void Move(int tarl,int tarr) {
    while( tarl < l ) --l , t += pba[r].query(in[l]-1) - pba[l].query(in[l]-1);
    while( r < tarr ) ++r , t += ( r - l + 1 ) - ( pba[r].query(in[r]) - ( l ? pba[l-1].query(in[r]) : 0 ) );
    while( l < tarl ) t -= pba[r].query(in[l]-1) - pba[l].query(in[l]-1) , ++l;
    while( tarr < r ) t -= ( r - l + 1 ) - ( pba[r].query(in[r]) - ( l ? pba[l-1].query(in[r]) : 0 ) ) , --r;
}

inline void solve(uint* dst,const uint* sou,int l_l,int l_r,int r_l,int r_r) {
    l_r = min( l_r , r_r );
    if( r_l == r_r ) {
        Move(min(l_r,r_l-1)+1,r_l);
        for(int i=min(l_r,r_l-1);i>=l_l;i--) {
            dst[r_l] = min( dst[r_l] , t + sou[i] );
            if(i) Move(i,r_l);
        }
        return;
    }
    const int r_mid = ( r_l + r_r ) >> 1;
    int l_mid;
    Move(min(l_r,r_mid-1)+1,r_mid);
    for(int i=min(l_r,r_mid-1);i>=l_l;i--) {
        if( sou[i] + t < dst[r_mid] ) dst[r_mid] = sou[i] + t , l_mid = i;
        if(i) Move(i,r_mid);
    }
    if( r_l < r_mid ) solve(dst,sou,l_l,l_mid,r_l,r_mid-1);
    if( r_mid < r_r ) solve(dst,sou,l_mid,l_r,r_mid+1,r_r);
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) ) ;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}


int main() {
    static int n,k,cur;
    n = getint() , k = getint() , memset(f[cur=0],0x7f,sizeof(f[0])) , f[cur][0] = 0;
    for(int i=1;i<=n;i++) pba[i] = pba[i-1] , pba[i].update(in[i]=getint());
    for(int i=1;i<=k;i++) cur ^= 1 , memset(f[cur],0x7f,sizeof(f[cur])) , f[cur][0] = 0 , solve(f[cur],f[cur^1],0,n,1,n);
    printf("%u\n",f[cur][n]);
}

