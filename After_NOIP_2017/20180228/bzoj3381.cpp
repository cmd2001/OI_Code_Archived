#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2.5e4+1e2,maxl=17;

int mi[maxn][maxl],Log[maxn];


inline void gen(int n) {
    for(int i=2;i<=n;i++) Log[i] = Log[i>>1] + 1;
    const int Lim = Log[n];
    for(int i=1;i<=Lim;i++) {
        const int h = 1 << ( i - 1 ) , len = 1 << i;
        for(int st=1;st+len-1<=n;st++)
            mi[st][i] = min( mi[st][i-1] , mi[st+h][i-1] );
    }
}
inline int query(int l,int r) {
    const int L = Log[r-l+1];
    return min( mi[l][L] , mi[r-(1<<L)+1][L] );
}
int main() {
    static int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",mi[i]);
    gen(n);
    for(int i=1,a,b;i<=q;i++) {
        scanf("%d%d",&a,&b);
        printf("%d\n",query(a,b));
    }
    return 0;
}
