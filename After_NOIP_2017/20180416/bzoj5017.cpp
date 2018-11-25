#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxnn=5e5+1e2,maxn=1e6+1e2,maxe=1e7+1e2;
const int mod=1e9+7;

lli in[maxnn],r[maxnn];
int rec[maxnn],islf[maxn],fs,n;

namespace Graph {
    int s[maxn],f[maxe],t[maxe],nxt[maxe],cnt;
    int id[maxn],deg[maxn],siz[maxn],arv[maxn],iid;
    int vis[maxn],ins[maxn],stk[maxn],dfn[maxn],low[maxn],top,dd;
    int ss[maxn],tt[maxe],nnxt[maxe];
    inline void addedge(int from,int to) {
        t[++cnt] = to , f[cnt] = from , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void aaddedge(int from,int to) {
        static int cnt = 0;
        tt[++cnt] = to , nnxt[cnt] = ss[from] , ss[from] = cnt;
    }
    inline void tarjan(int pos) {
        low[pos] = dfn[pos] = ++dd , vis[stk[++top]=pos] = ins[pos] = 1;
        for(int at=s[pos];at;at=nxt[at])
            if( !vis[t[at]] ) tarjan(t[at]) , low[pos] = min( low[pos] , low[t[at]] );
            else if( ins[t[at]] ) low[pos] = min( low[pos] , dfn[t[at]] );
        if( low[pos] == dfn[pos] ) {
            ++iid;
            do {
                const int x = stk[top--]; ins[x] = 0;
                siz[id[x]=iid] += islf[x];
            } while( ins[pos] );
        }
    }
    inline int dfs(int pos) {
        if( vis[pos] ) return arv[pos];
        vis[pos] = 1 , arv[pos] = siz[pos];
        vector<int> sons;
        for(int at=ss[pos];at;at=nnxt[at]) sons.push_back(tt[at]);
        sort(sons.begin(),sons.end());
        int len = unique(sons.begin(),sons.end()) - sons.begin() ;
        for(int i=0;i<len;i++) arv[pos] += dfs(sons[i]);
        return arv[pos];
    }
    inline void work() {
        for(int i=1;i<=fs;i++) if( !vis[i] ) tarjan(i);
        for(int i=1;i<=cnt;i++) if( id[f[i]] != id[t[i]] ) aaddedge(id[f[i]],id[t[i]]);
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=iid;i++) if( !vis[i] ) dfs(i);
    }
}


struct SegmentTree {
    int l[maxn],r[maxn],lson[maxn],rson[maxn],cnt;
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return void(islf[rec[ll]=pos]=1);
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , Graph::addedge(pos,lson[pos]) ,
        build(rson[pos]=++cnt,mid+1,rr) , Graph::addedge(pos,rson[pos]) ;
    }
    inline void update(int pos,const int &ll,const int &rr,const int &s) {
        if( rr < l[pos] || r[pos] < ll ) return;
        if( ll <= l[pos] && r[pos] <= rr ) return Graph::addedge(s,pos);
        update(lson[pos],ll,rr,s) , update(rson[pos],ll,rr,s);
    }
}sgt;

int main() {
    static lli ans;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",in+i,r+i);
    sgt.build(sgt.cnt=1,1,n);
    for(int i=1,ll,rr;i<=n;i++) {
        ll = lower_bound(in+1,in+1+n,in[i]-r[i]) - in , rr = upper_bound(in+1,in+1+n,in[i]+r[i]) - in - 1;
        sgt.update(1,ll,rr,rec[i]);
    }
    fs = sgt.cnt , Graph::work();
    for(int i=1;i<=n;i++) ans += (lli) i * Graph::arv[Graph::id[rec[i]]] , ans %= mod;
    printf("%lld\n",ans);
    return 0;
}
