#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
const int maxn=4e4+1e2,maxm=2e2+1e1;

int in[maxn],f[maxn],lst[maxn],prv[maxn],b[maxm];
int n,sq,full;

int main() {
    scanf("%d%*d",&n) , sq = std::sqrt(n) , full = 0;
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1;i<=sq;i++) b[i] = 1;
    memset(f,0x3f,sizeof(f)) , *f = 0;
    for(int i=1;i<=n;i++) {
        prv[i] = lst[in[i]] , lst[in[i]] = i;
        for(int j=1;j<=std::min(sq,full);j++)
            if( b[j] > prv[i] ) {
                while( b[j]++ && lst[in[b[j]-1]] != b[j]-1 ) ; 
            }
        full += !prv[i];
        for(int j=1;j<=std::min(sq,full);j++) f[i] = std::min( f[i] , f[b[j]-1] + j * j );
    }
    printf("%d\n",f[n]);
    return 0;
}
