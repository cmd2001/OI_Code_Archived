#include<cstdio>
#include<algorithm>
#define lli long long int
const int maxn=5e1+5e0,maxm=5e4+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int a[maxm],c[maxn][maxm],h[maxn];
int n,m,h0,b,pos;
lli ans=inf;

struct Node {
    int del,siz;
    friend bool operator < (const Node &a,const Node &b) {
        return a.del > b.del;
    }
}ns[maxm];

inline lli calc(int pos) {
    lli ret = h[pos] + h0;
    int used = 0;
    for(int i=1;i<=m;i++) {
        ret += (lli) c[pos][i] * a[i];
        ns[i] = (Node){c[pos][i]-c[0][i],a[i]};
    }
    std::sort(ns+1,ns+1+m);
    for(int i=1,t;i<=m&&used!=b;i++) {
        t = std::min( ns[i].siz , b - used );
        used += t , ret -= (lli) ns[i].del * t;
    }
    return ret;
}

int main() {
    scanf("%d%d%d%d",&m,&b,&h0,&n);
    for(int i=1;i<=m;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) scanf("%d",h+i);
    for(int i=0;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",c[i]+j);
    for(int i=1;i<=n;i++) {
        lli t = calc(i);
        if( t < ans ) ans = t , pos = i;
    }
    printf("%d\n%lld\n",pos,ans);
    return 0;
}
