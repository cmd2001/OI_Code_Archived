#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e4+1e2,maxm=1e5+1e2;

struct Edge {
    int a,b;
    lli l;
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.l < b.l;
    }
}ns[maxm];

struct FindUnionSet {
    int fa[maxn];
    
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline void merge(int x,int y) {
        x = findfa(x) , y = findfa(y);
        fa[x] = y;
    }
    inline void init(int n) {
        for(int i=1;i<=n;i++)
            fa[i] = i;
    }
}fus;

lli in[maxn],sum,mi=0x3f3f3f3f;
int n,m;

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) {
        scanf("%lld",in+i);
        mi = min( mi , in[i] );
    }
    //debug<<"inital sum = "<<sum<<endl;
    for(int i=1,a,b,l;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&l);
        ns[i] = (Edge){a,b,(lli)l*2+in[a]+in[b]};
    }
    
    fus.init(n);
    sort(ns+1,ns+1+m);
    
    for(int i=1;i<=m;i++) {
        const int a  = ns[i].a , b = ns[i].b ;
        const lli l = ns[i].l;
        if( fus.findfa(a) != fus.findfa(b) ) {
            fus.merge(a,b);
            sum += l;
        }
    }
    
    sum += mi;
    
    printf("%lld\n",sum);
    
    return 0;
}