#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=4e4+1e2,maxm=2e2+1e1;
const lli inf=0x3f3f3f3f3f3f3f3fLL;

int a[maxm][maxm],b[maxm][maxm],c[maxm][maxm],col[maxm][maxm];
int s[maxn],t[maxn<<5],nxt[maxn<<5];
lli f[maxn<<5],ans;
int dep[maxn];
int n,m,st,ed;

inline void coredge(int from,int to,int flow) {
   static int cnt = 1;
   t[++cnt] = to , f[cnt] = flow,
   nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
   coredge(from,to,flow);
   coredge(to,from,0);
}
inline void doubledge(int from,int to,int flow) {
   coredge(from,to,flow);
   coredge(to,from,flow);
}

inline bool bfs() {
   memset(dep,-1,sizeof(dep));
   dep[st] = 0;
   queue<int> q;
   q.push(st);
   while( q.size() ) {
       const int pos = q.front(); q.pop();
       for(int at=s[pos];at;at=nxt[at])
           if( f[at] && !~dep[t[at]] ) {
               dep[t[at]] = dep[pos] + 1;
               q.push(t[at]);
           }
   }
   return ~dep[ed];
}
inline lli dfs(int pos,lli flow) {
   if( pos == ed )
       return flow;
   lli ret = 0 , now = 0;
   for(int at=s[pos];at;at=nxt[at])
       if( f[at] && dep[t[at]] > dep[pos] ) {
           now = dfs(t[at],min(flow,f[at]));
           ret += now , flow -= now,
           f[at] -= now , f[at^1] += now;
           if( !flow )
               return ret;
       }
   if( !ret )
       dep[pos] = -1;
   return ret;
}
inline lli dinic() {
   lli ret = 0 , now = 0;
   while( bfs() ) {
       while( now = dfs(st,inf) )
           ret += now;
   }
   return ret;
}

inline int cov(int xx,int yy) {
   return ( xx - 1 ) * m + yy;
}

inline void build() {
   for(int i=1;i<=n;i++)
       for(int j=1;j<=m;j++)
           col[i][j] = !( ( i + j ) & 1 );
   st = cov(n,m) + 1 , ed = cov(n,m) + 2;
   //debug<<"st = "<<st<<"ed = "<<ed<<endl;
   for(int i=1;i<=n;i++)
       for(int j=1;j<=m;j++) {
           if( !col[i][j] ) {
               singledge(st,cov(i,j),a[i][j]);
               singledge(cov(i,j),ed,b[i][j]);
           }
           else {
               singledge(st,cov(i,j),b[i][j]);
               singledge(cov(i,j),ed,a[i][j]);
           }
       }
   for(int i=1;i<=n;i++)
       for(int j=1;j<=m;j++) {
           if( i+1 <= n )
               doubledge(cov(i,j),cov(i+1,j),c[i][j]+c[i+1][j]),
               ans += c[i][j]+c[i+1][j];
           if( j+1 <= m )
               doubledge(cov(i,j),cov(i,j+1),c[i][j]+c[i][j+1]),
               ans += c[i][j]+c[i][j+1];
       }
   
}

int main() {
    
   scanf("%d%d",&n,&m);
    
   for(int i=1;i<=n;i++)
       for(int j=1;j<=m;j++)
           scanf("%d",a[i]+j),
           ans += a[i][j];
   for(int i=1;i<=n;i++)
       for(int j=1;j<=m;j++)
           scanf("%d",b[i]+j),
           ans += b[i][j];
   for(int i=1;i<=n;i++)
       for(int j=1;j<=m;j++) {
           scanf("%d",c[i]+j);
       }
    
   build();
   
    
   printf("%lld\n",ans-dinic());
    
   return 0;
}
