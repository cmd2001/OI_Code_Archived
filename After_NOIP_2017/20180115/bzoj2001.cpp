#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e4+1e2,maxm=5e5+1e2,maxd=25;
const int inf=0x3f3f3f3f;

struct Edge {
    int a,b,val,id;
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.val < b.val;
    }
}ess[maxd][maxm],now[maxm],etp[maxm];
int opeid[maxm],opeval[maxm];
int wei[maxm],cov[maxm]; // weight of edge , convert reaL id to operated id.
int fa[maxn];
lli ans[maxm];

inline int findfa(int x) {
    return fa[x] == x ? x : fa[x] = findfa(fa[x]);
}
inline void merge(int x,int y) {
    x = findfa(x) , y = findfa(y);
    if( x == y ) return;
    fa[x] = y;
}
inline void reset(Edge* es,int len) {
    for(int i=1;i<=len;i++)
        fa[es[i].a] = es[i].a ,
        fa[es[i].b] = es[i].b;
}

inline lli contraction(Edge* es,int &len) {
    lli ret = 0;
    int tpl = 0;
    
    reset(es,len);
    sort(es+1,es+1+len);
    debug<<"in first for"<<endl;
    for(int i=1;i<=len;i++)
        if( findfa(es[i].a) != findfa(es[i].b) ) { // find a mst 
            debug<<"i = "<<i<<"faa = "<<findfa(es[i].a)<<"fab = "<<findfa(es[i].b)<<endl;
            etp[++tpl] = es[i] , merge(es[i].a,es[i].b);
        }
    
    reset(etp,tpl);
    debug<<"in second for"<<endl;
    for(int i=1;i<=tpl;i++)
        if( etp[i].val != -inf ) {
            debug<<"i = "<<i<<"faa = "<<findfa(etp[i].a)<<"fab = "<<findfa(etp[i].b)<<endl;
            ret += etp[i].val , merge(etp[i].a,etp[i].b);
        }
    
    tpl = 0;
    for(int i=1;i<=len;i++)
        if( findfa(es[i].a) != findfa(es[i].b) ) {
            etp[++tpl] = es[i];
            etp[tpl].a = findfa(es[i].a) , etp[tpl].b = findfa(es[i].b) ,
            cov[es[i].id] = tpl;
        }
    
    reset(es,len);
    len = tpl;
    memcpy(es+1,etp+1,sizeof(es[0])*len);
    
    return ret;
}
inline void reduction(Edge* es,int &len) {
    int tpl = 0;
    
    reset(es,len);
    sort(es+1,es+1+len);
    for(int i=1;i<=len;i++)
        if( findfa(es[i].a) != findfa(es[i].b) ) {
            merge(es[i].a,es[i].b);
            etp[++tpl] = es[i];
            cov[es[i].id] = tpl;
        }
        else if( es[i].val == inf ) {
            etp[++tpl] = es[i];
            cov[es[i].id] = tpl;
        }
    
    reset(es,len) , len = tpl;
    memcpy(es+1,etp+1,sizeof(es[0])*len);
}
inline lli mst(Edge* es,int len) {
    lli ret = 0;
    reset(es,len);
    sort(es+1,es+1+len);
    for(int i=1;i<=len;i++)
        if( findfa(es[i].a) != findfa(es[i].b) )
            ret += es[i].val , merge(es[i].a,es[i].b);
    return ret;
}

inline void solve(Edge* es,int dep,int len,int ll,int rr,lli res) {
    debug<<"dep = "<<dep<<"len = "<<len<<"ll = "<<ll<<"rr = "<<rr<<"res = "<<res<<endl;
    if( ll == rr )
        wei[opeid[ll]] = opeval[ll];
    for(int i=1;i<=len;i++) {
        es[i].val = wei[es[i].id];
        now[i] = es[i] , cov[now[i].id] = i;
    }
    if( ll == rr ) {
        debug<<"len = "<<len<<endl;
        debug<<"printing now"<<endl;
        for(int i=1;i<=len;i++)
            debug<<now[i].a<<" "<<now[i].b<<" "<<now[i].val<<endl;
        ans[ll] = res + mst(now,len);
        //reset(es,len);
        return;
    }
    
    debug<<"print edges"<<endl;
    for(int i=1;i<=len;i++)
        debug<<es[i].a<<" "<<es[i].b<<endl;
    
    for(int i=ll;i<=rr;i++) {
        now[cov[opeid[i]]].val = -inf;
        debug<<"cov = "<<cov[opeid[i]]<<endl;
    }
    res += contraction(now,len);
    
    
    for(int i=ll;i<=rr;i++)
        now[cov[opeid[i]]].val = inf;
    reduction(now,len);
    
    for(int i=1;i<=len;i++) debug<<now[i].id<<" ";debug<<endl;
    
    memcpy(ess[dep+1]+1,now+1,sizeof(now[0])*len);
    
    const int mid = ( ll + rr ) >> 1;
    solve(ess[dep+1],dep+1,len,ll,mid,res);
    solve(ess[dep+1],dep+1,len,mid+1,rr,res);
}

int main() {
    static int n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1,a,b,l;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&l);
        ess[0][l] = (Edge){a,b,l,i};
        wei[i] = l;
    }
    for(int i=1;i<=q;i++)
        scanf("%d%d",opeid+i,opeval+i);
    
    solve(ess[0],0,m,1,q,0);
    
    for(int i=1;i<=q;i++)
        printf("%lld\n",ans[i]);
    
    return 0;
}
