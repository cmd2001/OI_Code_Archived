#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=4e2+1e1;
const int mod=1e9+7,inv=(mod+1)>>1;

inline int add(const int &x,const int &y) {
    const int ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline int sub(const int &x,const int &y) {
    const int ret = x - y;
    return ret < 0 ? ret + mod : mod;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}

int in[maxn],n,t,cur;
int f[2][maxn][maxn],s2[maxn]; // colsed .

inline void dp(int dst[maxn][maxn],const int sou[maxn][maxn]) {
    static int sui[maxn][maxn],suj[maxn][maxn];
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j++)
        sui[i][j] = add(sui[i-1][j],mul(sou[i][j],i-1));
    for(int i=1;i<=n;i++) for(int j=n;j>=i;j--)
        suj[i][j] = add(suj[i][j+1],mul(sou[i][j],n-j));
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j++) {
        dst[i][j] = mul(sou[i][j],s2[i-1]+s2[n-j]+s2[j-i+1]);
        adde(dst[i][j],sui[i-1][j]) , adde(dst[i][j],suj[i][j+1]);
    }
}

inline void init() {
    in[0] = in[n+1] = 0x3f3f3f3f;
    for(int i=1;i<=n;i++) s2[i] = i * ( i + 1 ) >> 1;
    for(int i=1;i<=n;i++) {
        int mx = 0;
        for(int j=i;j<=n;j++) {
            mx = max( mx , in[j] );
            if( i == 1 && j == n ) f[0][i][j] = mx;
            else if( in[i-1] > mx && mx < in[j+1] ) f[0][i][j] = sub(mx,min(in[i-1],in[j+1]));
        }
    }
}

inline void getans() {
    for(int i=1;i<=n;i++) {
        int ans = 0;
        for(int l=1;l<=i;l++) for(int r=i;r<=n;r++) adde(ans,f[cur][l][r]);
        printf("%d%c",ans,i!=n?' ':'\n');
    }
}

int main() {
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    init();
    for(int i=1;i<=t;i++) cur ^= 1 , dp(f[cur],f[cur^1]);
    getans();
    return 0;
}
