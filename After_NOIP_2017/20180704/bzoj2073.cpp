#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=20,maxs=1<<16,inf=0x3f3f3f3f;

int t[maxn],w[maxn],n,lim,fs;
int su[maxs],mx[maxs],f[maxs];

int main() {
    scanf("%d%d",&lim,&n);
    for(int i=1;i<=n;i++) scanf("%d%d",t+i,w+i);
    fs = 1 << n; memset(f,0x3f,sizeof(f));
    for(int i=0;i<fs;i++) for(int j=1;j<=n;j++) if( i & ( 1 << ( j - 1 ) ) ) {
        su[i] += w[j] , mx[i] = max( mx[i] , t[j] );
    }
    for(int i=0;i<fs;i++) if( su[i] <= lim ) f[i] = mx[i];
    for(int sta=0;sta<fs;sta++) for(int ss=sta;ss;ss=(ss-1)&sta) f[sta] = min( f[sta] , f[ss] + f[sta^ss] );
    printf("%d\n",f[fs-1]);
    return 0;
}

