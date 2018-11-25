#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int in[maxn],app[maxn],bel[maxn],ans[maxn],ll,rr,now;
struct QNode {
    int l,r,id;
    friend bool operator < (const QNode &a,const QNode &b) {
        return bel[a.l] != bel[b.l] ? bel[a.l] < bel[b.l] : a.r < b.r;
    }
}ns[maxn];

inline void update(int pos,int x) {
    if( app[pos] == pos && app[pos] + x != pos ) --now;
    else if( app[pos] != pos && app[pos] + x == pos ) ++now;
    app[pos] += x;
}
inline void solve(int tarl,int tarr,int id) {
    while( tarl < ll ) update(in[--ll],1);
    while( ll < tarl ) update(in[ll++],-1);
    while( rr < tarr ) update(in[++rr],1);
    while( tarr < rr ) update(in[rr--],-1);
    ans[id] = now;
}

inline void fill(int n) {
    int blk = sqrt(n) , cnt = 0;
    for(int i=1,j;i<=n;i=j+1) {
        j = min( i + blk - 1 , n ) , ++cnt;
        for(int k=i;k<=j;k++)
            bel[k] = cnt;
    }
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&ns[i].l,&ns[i].r) , ns[i].id = i;
    
    fill(n);
    sort(ns+1,ns+1+m);
    
    app[in[ll=rr=1]] = 1;
    for(int i=1;i<=m;i++)
        solve(ns[i].l,ns[i].r,ns[i].id);
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    
    return 0;
}