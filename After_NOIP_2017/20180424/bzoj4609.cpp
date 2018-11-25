#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
typedef long long int lli;
using namespace std;
const int maxn=5e3+1e2,maxe=5e4+1e2;

int tp[maxn];
lli su[maxn],f[2][maxn];
int b,s,cur;

struct Graph {
    int s[maxn],t[maxe],nxt[maxe],l[maxe],dis[maxn],inq[maxn],cnt;
    inline void addedge(int from,int to,int len) {
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void spfa(int st) {
        memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
        queue<int> q; q.push(st) , inq[st] = 1;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , inq[pos] = 0;
            for(int at=s[pos];at;at=nxt[at])
                if( dis[t[at]] > dis[pos] + l[at] ) {
                    dis[t[at]] = dis[pos] + l[at];
                    if( !inq[t[at]] ) q.push(t[at]);
                }
        }
    }
}gra,rev;

inline void dp() {
    for(int i=1;i<=b;i++) su[i] = (lli) gra.dis[i] + rev.dis[i];
    sort(su+1,su+1+b) , memset(f,0x3f,sizeof(f)) , **f = 0;
    for(int i=1;i<=b;i++) su[i] += su[i-1];
    for(int j=1;j<=s;j++) { // j is number of groups .
        cur ^= 1 , memset(f[cur],0x3f,sizeof(f[1]));
        for(int i=1;i<=b;i++) // i is last node .
            for(int lst=tp[i];lst<i;lst++)
                if( f[cur][i] >= f[cur^1][lst] + ( i - lst - 1 ) * ( su[i] - su[lst] ) ) f[cur][i] = f[cur^1][lst] + ( i - lst - 1 ) * ( su[i] - su[lst] ) , tp[i] = lst;
    }
}

int main() {
    static int n,r;
    scanf("%d%d%d%d",&n,&b,&s,&r);
    for(int i=1,a,b,l;i<=r;i++) scanf("%d%d%d",&a,&b,&l) , gra.addedge(a,b,l) , rev.addedge(b,a,l);
    gra.spfa(b+1) , rev.spfa(b+1) , dp();
    printf("%lld\n",f[cur][b]);
    return 0;
}
