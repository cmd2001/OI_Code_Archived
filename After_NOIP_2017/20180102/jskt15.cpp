#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=7e2+1e1,maxm=5e4+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm<<2],nxt[maxm<<2],c[maxm<<2],f[maxm<<2];
int dis[maxn],sou[maxn],inq[maxn];
int in[12][62];
int n,m,st,ed;
double ans;

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
    memset(dis,inf,sizeof(dis));
    memset(sou,0,sizeof(sou));
    dis[st] = 0;
    queue<int> q;
    q.push(st) , inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        //debug<<"pos = "<<pos<<endl;
        inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at]) {
            //debug<<"at = "<<at<<endl;
            if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at];
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
    for(int pos=ed;pos!=st;pos=t[sou[pos]^1]) {
        //debug<<"sou = "<<sou[pos]<<endl;
        //debug<<"pos = "<<pos<<endl;
        if( !pos )
            exit(0);
        ret = min( ret , f[sou[pos]] );
    }
    for(int pos=ed;pos!=st;pos=t[sou[pos]^1])
        f[sou[pos]] -= ret , f[sou[pos]^1] += ret;
    return ret;
}

inline int calc() {
    int ret = 0 , dd , now;
    while( spfa() ) {
        dd = dis[ed];
        //debug<<"in release"<<endl;
        now = release();
        //debug<<"now = "<<now<<endl;
        ret += dd * now;
    }
    //debug<<"returning"<<endl;
    return ret;
}

inline int covl(int id,int t) {
    return ( t - 1 ) * m + id;
}
inline int covr(int id) {
    return n * m + id;
}

int main() {
    scanf("%d%d",&m,&n);
    st = n * m + n + 1 , ed = n * m + n + 2;
    
    for(int j=1;j<=n;j++)
        for(int i=1;i<=m;i++)
            scanf("%d",in[i]+j);
    
    for(int tar=1;tar<=n;tar++)
        addedge(covr(tar),ed,0,1);
    for(int id=1;id<=m;id++)
        for(int t=1;t<=n;t++) {
            int c = covl(id,t);
            addedge(st,c,0,1);
            for(int tar=1;tar<=n;tar++)
                addedge(c,covr(tar),in[id][tar]*t,1);
        }
    
    //debug<<"inputed"<<endl;
    ans = calc();
    
    ans /= n;
    
    //debug<<ans<<endl;
    printf("%0.2lf\n",ans);
    
    return 0;
}