#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e2+1e1,maxm=1e4+1e2;
const int inf=0x3f3f3f3f;

int n,m,st,ed;

struct ValFlow {
    int s[maxn<<1],t[maxm<<4],nxt[maxm<<4],c[maxm<<4],f[maxm<<4];
    int dis[maxn],sou[maxn],inq[maxn];

    inline void coredge(int from,int to,int cost,int flow) {
        static int cnt = 1;
        t[++cnt] = to , c[cnt] = cost , f[cnt] = flow,
        nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int from,int to,int cost,int flow) {
        //debug<<"from = "<<from<<" to = "<<to<<" cost = "<<cost<<" flow = "<<flow<<endl;
        coredge(from,to,cost,flow);
        coredge(to,from,-cost,0);
    }
    
    inline bool spfa() {
        //debug<<"in spfa"<<endl;
        memset(dis,inf,sizeof(dis));
        memset(sou,0,sizeof(sou));
        memset(inq,0,sizeof(inq));
        dis[st] = 0;
        queue<int> q;
        q.push(st) , inq[st]=1;
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            inq[pos] = 0;
            //debug<<"pos = "<<pos<<endl;
            for(int at=s[pos];at;at=nxt[at]) {
                //debug<<"t = "<<t[at]<<"f = "<<f[at]<<endl;
                if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                    dis[t[at]] = dis[pos] + c[at],
                    sou[t[at]] = at;
                    if( !inq[t[at]] ) {
                        q.push(t[at]);
                        inq[t[at]] = 1;
                    }
                }
            }
        }
        return dis[ed] != inf;
    }
    
    inline int release() {
        int ret = inf;
        for(int pos=ed;pos!=st;pos=t[sou[pos]^1])
            ret = min( ret , f[sou[pos]] );
        for(int pos=ed;pos!=st;pos=t[sou[pos]^1])
            f[sou[pos]] -= ret , f[sou[pos]^1] += ret;
        return ret;
    }
    
    inline lli calc() {
        lli ret = 0 , cost = 0 , flow = 0 , fullf = 0;
        while( spfa() ) {
            cost = dis[ed];
            flow = release();
            fullf += flow;
            ret += cost * flow;
        }
        //debug<<"full flow = "<<fullf<<endl;
        return ret;
    }
        
}mxf,mif;

inline void addedge(int from,int to,int cost,int flow) {
    mxf.addedge(from,to,-cost,flow);
    mif.addedge(from,to,cost,flow);
}

int main() {
    //freopen("dat.txt","r",stdin);
    scanf("%d%d",&m,&n),
    st = n + m + 1 , ed = n + m + 2;
    for(int i=1,v;i<=m;i++) {
        scanf("%d",&v);
        addedge(st,i,0,v);
    }
    for(int i=1,v;i<=n;i++) {
        scanf("%d",&v);
        addedge(i+m,ed,0,v);
    }
    for(int i=1,v;i<=m;i++)
        for(int j=1;j<=n;j++) {
            scanf("%d",&v);
            addedge(i,j+m,v,inf);
        }
    
    printf("%lld\n%lld\n",mif.calc(),-mxf.calc());
    return 0;
}