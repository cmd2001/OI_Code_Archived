#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
/*#include<iostream>
using namespace std;
#define debug cout*/
const int maxn=5e3+1e1,maxm=1.8e5+1e2,maxe=1.5e6+1e2;
const int inf=0x3f3f3f3f,lim=1e9;

int a[maxn],b[maxn],w[maxn],l[maxn],r[maxn],p[maxn];

namespace NetworkFlow {
    int s[maxm],t[maxe<<1],nxt[maxe<<1],f[maxe<<1],pcnt;
    int dep[maxm],st,ed;
    inline void coredge(int from,int to,int flow) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow) {
        //debug<<"from = "<<from<<"to = "<<to<<"flow = "<<flow<<endl;
        //if( 9 == from ) debug<<"pos ===================== 9"<<endl;
        coredge(from,to,flow) , coredge(to,from,0);
    }
    inline bool bfs() {
        memset(dep,-1,sizeof(dep)) , dep[st] = 0;
        std::queue<int> q; q.push(st);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int at=s[pos];at;at=nxt[at])
                if( f[at] && !~dep[t[at]] )
                    dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
        }
        return ~dep[ed];
    }
    inline int dfs(int pos,int flow) {
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at])    
            if( f[at] && dep[t[at]] > dep[pos] ) {
                now = dfs(t[at],std::min(flow,f[at])) ,
                ret += now , flow -= now , 
                f[at] -= now , f[at^1] += now;
                if( !flow ) return ret;
            }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline int dinic() {
        int ret = 0;
        while( bfs() ) ret += dfs(st,inf);
        return ret;
    }
}
using namespace NetworkFlow;

namespace PersistentSegmentTree {
    int lson[maxm],rson[maxm],id[maxm],cnt;
    inline void insert(int &pos,int pre,int l,int r,const int &tar,const int &sou) { // insert white .
        id[pos=++cnt] = ++pcnt;
        //debug<<"pos = "<<pos<<"id = "<<pcnt<<endl;
        if( pre ) singledge(id[pos],id[pre],inf);
        if( l == r ) return singledge(id[pos],sou,inf);
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],lson[pre],l,mid,tar,sou) , singledge(id[pos],id[lson[pos]],inf) , rson[pos] = rson[pre];
        else insert(rson[pos],rson[pre],mid+1,r,tar,sou) , singledge(id[pos],id[rson[pos]],inf) , lson[pos] = lson[pre];
    }
    inline void query(int pos,int l,int r,const int &ll,const int &rr,const int &sou) {
        //debug<<"pos = "<<pos<<"ll = "<<ll<<"rr = "<<rr<<"l = "<<l<<"r = "<<r<<endl;
        if( !pos ) return;
        if( ll <= l && r <= rr ) return singledge(sou,id[pos],inf);
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) query(lson[pos],l,mid,ll,rr,sou);
        else if( ll > mid ) query(rson[pos],mid+1,r,ll,rr,sou);
        else query(lson[pos],l,mid,ll,rr,sou) , query(rson[pos],mid+1,r,ll,rr,sou);
    }
}
using namespace PersistentSegmentTree;

int root[maxn];

int main() {
    static int n,ans;
    scanf("%d",&n) , st = n * 3 + 1 , pcnt = ed = st + 1;
    #define cov(x,tpe) (x*3-2+tpe)
    for(int i=1;i<=n;i++) {
        scanf("%d%d%d%d%d%d",a+i,b+i,w+i,l+i,r+i,p+i) , ans += b[i] + w[i];
        singledge(st,cov(i,0),b[i]) , /*singledge(cov(i,0),cov(i,0),inf) ,*/ singledge(cov(i,0),ed,w[i]) , singledge(cov(i,0),cov(i,2),p[i]);
        query(root[i-1],0,lim,l[i],r[i],cov(i,2)) , insert(root[i],root[i-1],0,lim,a[i],cov(i,0));
    }
    ans -= dinic() , printf("%d\n",ans);
    return 0;
}
