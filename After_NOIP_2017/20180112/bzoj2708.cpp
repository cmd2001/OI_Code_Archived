#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=55;

int in[maxn],f[maxn],n;

inline int calc(int l,int r) {
    for(int k=1;k<=r-k+1;k++) {
        for(int j=l+k;j<=r;j++)
            if( in[j] - in[j-k] > 1 )
                return k-1;
        if( in[r-k+1] - in[l+k-1] <= 1 )
            return k-1;
    }
    return r-l+1;
}

inline void getans() {
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++)
        for(int j=0;j<i;j++)
            f[i] = max( f[i] , f[j] + calc(j+1,i) );
}

int main() {
    while( scanf("%d",&n) == 1 ) {
        for(int i=1;i<=n;i++)
            scanf("%d",in+i);
        sort(in+1,in+1+n);
        getans();
        printf("%d\n",f[n]);
    }
    return 0;
}