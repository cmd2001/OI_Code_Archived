#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=2e4+1e2,lim=2e4;
const int inf=0x3f3f3f3f;

int f[maxn];
int in[maxn];

inline void update(int x,int cost) {
    for(int i=lim;i>=x;i--)
        f[i] = min( f[i] , f[i-x] + cost );
}
inline void bindiv(int x,int c) {
    for(int i=1;i<=c;i<<=1) {
        c -= i;
        update(x*i,i);
    }
    if( c )
        update(x*c,c);
}

int main() {
    static int n,q;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    memset(f,0x3f,sizeof(f)) , *f = 0;
    for(int i=1,c;i<=n;i++) {
        scanf("%d",&c);
        bindiv(in[i],c);
    }
    while( scanf("%d",&q) == 1 )
        printf("%d\n",f[q]!=inf?f[q]:-1);
    return 0;
}
