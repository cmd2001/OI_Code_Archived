#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=2e4+1e2,maxe=1e5+1e2,maxb=145;
const int inf=0x3f3f3f3f;

int n,m,q;
struct Array {
    int dat[maxn];
    int* operator [] (const int &x) { return dat+(x-1)*m; }
}r,c,dis;

int ans[maxe];
struct Query {
    int x,y,xx,yy,id;
}qs[maxe],tp[2][maxe];

struct Node {
    int dis,px,py;
    friend bool operator < (const Node &a,const Node &b) {
        return a.dis > b.dis;
    }
};


inline void update(priority_queue<Node> &q,int tx,int ty,int nd) {
    if( dis[tx][ty] > nd ) q.push((Node){dis[tx][ty]=nd,tx,ty});
}
inline void dji(int sx,int sy,int tx,int ty,int xx,int yy) {
    for(int i=sx;i<=tx;i++) for(int j=sy;j<=ty;j++) dis[i][j] = inf;
    priority_queue<Node> q; q.push((Node){dis[xx][yy]=0,xx,yy});
    while( q.size() ) {
        int x = q.top().px , y = q.top().py , dd = q.top().dis; q.pop();
        if( dd != dis[x][y] ) continue;
        if( x != n ) update(q,x+1,y,dd+c[x][y]);
        if( x != 1 ) update(q,x-1,y,dd+c[x-1][y]);
        if( y != m ) update(q,x,y+1,dd+r[x][y]);
        if( y != 1 ) update(q,x,y-1,dd+r[x][y-1]);
    }
}

inline void solve(int sx,int sy,int tx,int ty,int ql,int qr) {
    if( sx > tx || sy > ty || ql > qr ) return;
    if( tx - sx < ty - sy ) {
        const int midy = ( sy + ty ) >> 1;
        for(int i=sx;i<=tx;i++) {
            dji(sx,sy,tx,ty,i,midy);
            for(int i=ql;i<=qr;i++) ans[qs[i].id] = min( ans[qs[i].id] , dis[qs[i].x][qs[i].y] + dis[qs[i].xx][qs[i].yy] );
        }
        if( sx == tx && sy == ty ) return;
        int tpl = 0 , tpr = 0;
        for(int i=ql;i<=qr;i++) {
            if( qs[i].y < midy && qs[i].yy < midy ) tp[0][++tpl] = qs[i];
            else if( qs[i].y > midy && qs[i].yy > midy ) tp[1][++tpr] = qs[i];
        }
        const int qmid = ql + tpl - 1 , nqr = qmid + tpr;
        memcpy(qs+ql,tp[0]+1,sizeof(Query)*tpl) , memcpy(qs+qmid+1,tp[1]+1,sizeof(Query)*tpr);
        solve(sx,sy,tx,midy,ql,qmid) , solve(sx,midy+1,tx,ty,qmid+1,nqr);
    } else {
        const int midx = ( sx + tx ) >> 1;
        for(int i=sy;i<=ty;i++) {
            dji(sx,sy,tx,ty,midx,i);
            for(int i=ql;i<=qr;i++) ans[qs[i].id] = min( ans[qs[i].id] , dis[qs[i].x][qs[i].y] + dis[qs[i].xx][qs[i].yy] );
        }
        if( sx == tx && sy == ty ) return;
        int tpl = 0 , tpr = 0;
        for(int i=ql;i<=qr;i++) {
            if( qs[i].x < midx && qs[i].xx < midx ) tp[0][++tpl] = qs[i];
            else if( qs[i].x > midx && qs[i].xx > midx ) tp[1][++tpr] = qs[i];
        }
        const int qmid = ql + tpl - 1 , nqr = qmid + tpr;
        memcpy(qs+ql,tp[0]+1,sizeof(Query)*tpl) , memcpy(qs+qmid+1,tp[1]+1,sizeof(Query)*tpr);
        solve(sx,sy,midx,ty,ql,qmid) , solve(midx+1,sy,tx,ty,qmid+1,nqr);
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) for(int j=1;j<m;j++) scanf("%d",r[i]+j);
    for(int i=1;i<n;i++) for(int j=1;j<=m;j++) scanf("%d",c[i]+j);
    scanf("%d",&q) , memset(ans,0x3f,sizeof(ans));
    for(int i=1;i<=q;i++) scanf("%d%d%d%d",&qs[i].x,&qs[i].y,&qs[i].xx,&qs[i].yy) , qs[i].id = i;
    solve(1,1,n,m,1,q);
    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
    return 0;
}
