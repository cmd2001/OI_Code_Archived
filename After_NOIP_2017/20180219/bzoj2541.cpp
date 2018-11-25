#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=4e3+1e2,maxm=1.6e4+1e3,maxe=1.3e5+1e2;
const int inf=0x3f3f3f3f;

int x[maxn],xx[maxn],y[maxn],yy[maxn];
int s[maxm],t[maxe<<1],nxt[maxe<<1],dis[maxm];
int n,sx,tx,sy,ty,ans=inf;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline int cov(int id,int sta) { // left -> 1 , up -> 2 , right -> 3 , down -> 4 .
    return 4 * ( id - 1 ) + sta;
}
inline void movel(int sx,int sy,int id) {
    int tar = 0;
    for(int i=1;i<=n;i++)
        if( y[i] <= sy && sy <= yy[i] && xx[i] <= sx ) {
            if( !tar ) tar = i;
            else if( xx[tar] < xx[i] ) tar = i;
        }
    if( tar ) addedge(id,cov(tar,3));
}
inline void mover(int sx,int sy,int id) {
    int tar = 0;
    for(int i=1;i<=n;i++)
        if( y[i] <= sy && sy <= yy[i] && sx <= x[i] ) {
            if( !tar ) tar = i;
            else if( x[i] < x[tar] ) tar = i;
        }
    if( tar ) addedge(id,cov(tar,1));
}
inline void moveu(int sx,int sy,int id) {
    int tar = 0;
    for(int i=1;i<=n;i++)
        if( x[i] <= sx && sx <= xx[i] && sy <= y[i] ) {
            if( !tar ) tar = i;
            else if( y[i] < y[tar] ) tar = i;
        }
    if( tar ) addedge(id,cov(tar,4));
}
inline void moved(int sx,int sy,int id) {
    int tar = 0;
    for(int i=1;i<=n;i++)
        if( x[i] <= sx && sx <= xx[i] && yy[i] <= sy ) {
            if( !tar ) tar = i;
            else if( yy[tar] < yy[i] ) tar = i;
        }
    if( tar ) addedge(id,cov(tar,2));
}
queue<int> q;
inline void bfs(int pos) {
    for(int at=s[pos];at;at=nxt[at])
        if( !~dis[t[at]] ) {
            dis[t[at]] = dis[pos] + 1 ,
            q.push(t[at]);
        }
}
inline void getans() {
    memset(dis,-1,sizeof(dis)) , *dis = 0;
    q.push(0);
    while( q.size() ) {
        bfs(q.front()) , q.pop();
    }
}

int main() {
    scanf("%d%d%d%d%d",&n,&sx,&sy,&tx,&ty);
    for(int i=1;i<=n;i++) scanf("%d%d%d%d",x+i,y+i,xx+i,yy+i);
    x[++n] = tx , xx[n] = tx , y[n] = ty , yy[n] = ty;
    movel(sx,sy,0) , mover(sx,sy,0) , moveu(sx,sy,0) , moved(sx,sy,0);
    for(int i=1;i<n;i++) {
        movel(x[i]-1,y[i]-1,cov(i,4)) , movel(x[i]-1,yy[i]+1,cov(i,2)) ,
        mover(xx[i]+1,y[i]-1,cov(i,4)) , mover(xx[i]+1,yy[i]+1,cov(i,2)) ,
        moveu(x[i]-1,yy[i]+1,cov(i,1)) , moveu(xx[i]+1,yy[i]+1,cov(i,3)) ,
        moved(x[i]-1,y[i]-1,cov(i,1)) , moved(xx[i]+1,y[i]-1,cov(i,3)) ;
    }
    getans();
    for(int i=1;i<=4;i++)
        if( ~dis[cov(n,i)] ) ans = min( ans , dis[cov(n,i)] );
    if( ans == inf ) ans = 0;
    printf("%d\n",ans);
    return 0;
}
