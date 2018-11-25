#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=257,lim=256;

lli in[maxn];
lli cst[maxn][maxn],f[maxn][maxn];
int d,k;

inline lli calc(int l,int r,int val) {
    lli ret = 0;
    for(int i=l;i<=r;i++) ret += in[i] * ( i - val ) * ( i - val );\
    return ret;
}
inline void getcst() {
    for(int l=1;l<=lim;l++) {
        for(int r=l,t=l;r<=lim;r++) {
            while( t < r && calc(l,r,t+1) <= calc(l,r,t) ) ++t;
            cst[l][r] = calc(l,r,t);
        }
    }
}
inline void dp() {
    memset(f,0x3f,sizeof(f)) , f[0][0] = 0;
    for(int i=1;i<=lim;i++) {
        for(int j=1;j<=min(i,k);j++)
            for(int lst=0;lst<i;lst++)
                f[i][j] = min( f[i][j] , f[lst][j-1] + cst[lst+1][i] );
    }
}

int main() {
    scanf("%d%d",&d,&k);
    for(int i=1,a;i<=d;i++) scanf("%d",&a) , scanf("%lld",in + ++a);
    getcst() , dp() , printf("%lld\n",f[lim][k]);
    return 0;
}
