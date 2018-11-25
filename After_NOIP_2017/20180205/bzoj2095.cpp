#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=4e3+1e2;
const int inf=0x3f3f3f3f;

int x[maxn],y[maxn],a[maxn],b[maxn];
int srt[maxn<<1],len;
int in[maxn],out[maxn];
int n,m,ans;

namespace Flow {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],f[maxn<<1],dep[maxn],cnt;
    int st,ed;
    
    inline void coredge(int from,int to,int flow) {
        t[++cnt] = to , f[cnt] = flow ,
        nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow) {
        //debug<<"from = "<<from<<"to = "<<to<<endl;
        coredge(from,to,flow) , coredge(to,from,0);
    }
    inline void doubledge(int from,int to,int flow) {
        //debug<<"from = "<<from<<"to = "<<to<<endl;
        coredge(from,to,flow) , coredge(to,from,flow);
    }
    inline bool bfs() {
        memset(dep,-1,sizeof(dep)) , dep[st] = 0;
        queue<int> q; q.push(st);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int at=s[pos];at;at=nxt[at])
                if( f[at] && !~dep[t[at]] ) dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
        }
        //debug<<"dep = "<<dep[ed]<<endl;
        return ~dep[ed];
    }
    inline int dfs(int pos,int flow) {
        //debug<<"pos = "<<pos<<endl;
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dep[t[at]] > dep[pos] ) {
                now = dfs(t[at],min(flow,f[at]));
                ret += now , flow -= now ,
                f[at] -= now , f[at^1] += now;
                if( !flow ) return ret;
            }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline int dinic() {
        int ret = 0 , now = 0;
        while( bfs() ) {
            while( now = dfs(st,inf) ) ret += now;
        }
        //debug<<"ret = "<<ret<<endl;
        return ret;
    }
    inline int build(int t) {
        memset(s,0,sizeof(s)) , cnt = 1 , st = n + 1 , ed = st + 1;
        memset(in,0,sizeof(in)) , memset(out,0,sizeof(out));
        for(int i=1;i<=m;i++) {
            if( min(a[i],b[i]) > t ) return -1;
            else if( max(a[i],b[i]) <= t ) doubledge(x[i],y[i],1) , ++in[x[i]] , ++out[y[i]];
            else if( a[i] <= t ) ++in[x[i]],++out[y[i]];
            else if( b[i] <= t ) ++out[x[i]],++in[y[i]];
        }
        //for(int i=1;i<=n;i++) debug<<in[i]<<" "<<out[i]<<endl;
        for(int i=1;i<=n;i++)
            if( in[i] > out[i] ) singledge(st,i,(in[i]-out[i])>>1);
            else if( in[i] < out[i] ) singledge(i,ed,(out[i]-in[i])>>1);
        return 0;
    }
    inline bool judge(int t) {
        //debug<<"t = "<<t<<endl;
        if( !~build(t) ) return 0;
        int full = 0;
        for(int i=1;i<=n;i++) {
            if( in[i] > out[i] ) full += ( in[i] - out[i] ) >> 1;
            if( ( in[i] - out[i] ) & 1 ) return 0;
        }
        //debug<<"full = "<<full<<endl;
        return dinic() == full;
    }
}

inline int bin() {
    int ll = 0 , rr = len + 1 , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( Flow::judge(mid) ) rr = mid;
        else ll = mid;
    }
    return rr;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d%d",x+i,y+i,a+i,b+i) , srt[++len] = a[i] , srt[++len] = b[i];
    sort(srt+1,srt+1+len) , len = unique(srt+1,srt+1+len) - srt - 1;
    //debug<<"len = "<<len<<endl;
    for(int i=1;i<=m;i++)
        a[i] = lower_bound(srt+1,srt+1+len,a[i]) - srt ,
        b[i] = lower_bound(srt+1,srt+1+len,b[i]) - srt ;
    //for(int i=1;i<=m;i++) debug<<a[i]<<" "<<b[i]<<endl;
    ans = bin();
    if( ans > len ) puts("NIE");
    else {
        printf("%d\n",srt[ans]);
        //for(int i=1;i<=n;i++) printf("%d%c",i,i!=n?' ':'\n');
    }
    return 0;
}
