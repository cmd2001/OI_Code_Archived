#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=2e2+1e1,maxm=maxn*maxn*3;
const double pi = acos(-1.0);

int fa[maxm];
double siz[maxm];
char in[maxn][maxn];
int n,m;

inline int findfa(int x) {
    if( fa[x] == x ) return x;
    siz[fa[x]] += siz[x] , siz[x] = 0;
    return fa[x] = findfa(fa[x]);
}
inline void merge(int x,int y) {
    x = findfa(x) , y = findfa(y);
    if( x == y ) return;
    fa[y] = x, siz[x] += siz[y] , siz[y] = 0;
}
inline int covblk(int x,int y) {
    return m * ( x - 1 ) + y;
}
inline int cov(int x,int y,int id) {
    int bid = covblk(x,y);
    return 3 * ( bid - 1 ) + id;
}
inline int cov(int bid,int id) {
    return 3 * ( bid - 1 ) + id;
}
inline void merge_right(int lid,int rid,int ls,int rs) {
    if( ls == 0 ) {
        if( rs == 0 ) {
            merge(cov(lid,2),cov(rid,1));
            merge(cov(lid,3),cov(rid,2));
        } else if( rs == 1 ) {
            merge(cov(lid,2),cov(rid,2));
            merge(cov(lid,3),cov(rid,3));
        }
    } else if( ls == 1 ) {
        if( rs == 0 ) {
            merge(cov(lid,1),cov(rid,1));
            merge(cov(lid,2),cov(rid,2));
        } else if( rs == 1 ) {
            merge(cov(lid,1),cov(rid,2));
            merge(cov(lid,2),cov(rid,3));
        }
    }
}
inline void merge_down(int uid,int did,int us,int ds) {
    if( us == 0 ) {
        if( ds == 0 ) {
            merge(cov(uid,2),cov(did,1));
            merge(cov(uid,3),cov(did,2));
        } else if( ds == 1 ) {
            merge(cov(uid,2),cov(did,2));
            merge(cov(uid,3),cov(did,1));
        }
    } else if( us == 1 ) {
        if( ds == 0 ) {
            merge(cov(uid,2),cov(did,2));
            merge(cov(uid,3),cov(did,1));
        } else if( ds == 1 ) {
            merge(cov(uid,2),cov(did,1));
            merge(cov(uid,3),cov(did,2));
        }
    }
}
inline int getbel(int xx,int yy) {
    if( ( xx & 1 ) != ( yy & 1 ) ) return -1;
    if( !xx && !yy ) return !in[1][1] ? cov(1,1,1) : cov(1,1,2);
    if( !yy ) return in[xx>>1][1] ? cov(xx>>1,1,3) : cov(xx>>1,1,2);
    if( !xx ) return in[1][yy>>1] ? cov(1,yy>>1,1) : cov(1,yy>>1,2);
    if( ( xx & 1 ) && ( yy & 1 ) ) {
        int bx = ( xx + 1 ) >> 1 , by = ( yy + 1 ) >> 1;
        return cov(bx,by,2);
    } else if( !( xx & 1 ) && !( yy & 1 ) ) {
        int bx = xx >> 1 , by = yy >> 1;
        return !in[bx][by] ? cov(bx,by,3) : cov(bx,by,2);
    }
    throw "It shouldn't be here";
}

inline void init() {
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            int b = covblk(i,j);
            for(int k=1;k<=3;k++) {
                int id = cov(b,k);
                fa[id] = id;
                if( k & 1 ) siz[id] = pi / 4.0;
                else siz[id] = 4 - ( pi / 2.0 );
            }
        }
}
inline void mergesme() {
    for(int i=1;i<=n;i++)
        for(int j=1;j<m;j++)
            merge_right(covblk(i,j),covblk(i,j+1),in[i][j],in[i][j+1]);
    for(int i=1;i<n;i++)
        for(int j=1;j<=m;j++)
            merge_down (covblk(i,j),covblk(i+1,j),in[i][j],in[i+1][j]);
    int full = n * m * 3;
    for(int i=1;i<=full;i++) findfa(i);
}

int main() {
    static double ans;
    static int q;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) {
        scanf("%s",in[i]+1);
        for(int j=1;j<=m;j++) in[i][j] -= '0';
    }
    init();
    mergesme();
    scanf("%d",&q);
    for(int i=1,x,y,id;i<=q;i++) {
        scanf("%d%d",&x,&y);
        id = getbel(x,y) , ans = 0.0;
        if( !~id ) printf("%0.4lf\n",ans);
        else {
            id = findfa(id);
            ans = siz[id];
            printf("%0.4lf\n",ans);
        }
    }
    return 0;
}



