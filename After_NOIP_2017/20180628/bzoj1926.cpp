#include<cstdio>
#include<cctype>
typedef long long int lli;

int r,c,m;

namespace IO {
    inline char nextchar() {
        static const int BS = 1 << 21;
        static char buf[BS],*st,*ed;
        if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
        return st == ed ? -1 : *st++;
    }
    inline int getint() {
        int ret = 0 , ch;
        while( !isdigit(ch=nextchar()) ) ;
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
}
using IO::getint;

namespace Task1 {
    const int maxn=2e2+1e1,maxl=1e3+1e2,lim=1e3;
    int sum[maxl][maxn][maxn];
    unsigned short siz[maxl][maxn][maxn];
    inline void build() {
        for(int dep=lim;~dep;dep--) {
            for(int i=1;i<=r;i++) for(int j=1;j<=c;j++) sum[dep][i][j] += sum[dep][i][j-1] , siz[dep][i][j] += siz[dep][i][j-1];
            for(int i=1;i<=r;i++) for(int j=1;j<=c;j++) sum[dep][i][j] += sum[dep][i-1][j] , siz[dep][i][j] += siz[dep][i-1][j];
            for(int i=1;i<=r;i++) for(int j=1;j<=c;j++) {
                sum[dep][i][j] += sum[dep+1][i][j] , 
                siz[dep][i][j] += siz[dep+1][i][j] ;
            }
        }
    }
    #define sqsu(sou,x,y,xx,yy) (sou[xx][yy]+sou[x-1][y-1]-sou[x-1][yy]-sou[xx][y-1])
    inline int binLev(int x,int y,int xx,int yy,int ned) {
        if( sqsu(sum[0],x,y,xx,yy) < ned ) return -1;
        int l = 1 , r = lim + 1 , mid;
        while( r > l + 1 ) {
            mid = ( l + r ) >> 1;
            if( sqsu(sum[mid],x,y,xx,yy) >= ned ) l = mid;
            else r = mid;
        }
        return l;
    }
    inline int solve(int x,int y,int xx,int yy,int ned) {
        int last = binLev(x,y,xx,yy,ned);
        if( !~last ) return -1;
        ned -= sqsu(sum[last+1],x,y,xx,yy);
        return sqsu(siz[last+1],x,y,xx,yy) + ( ned + last - 1 ) / last;
    }
    inline void work() {
        for(int i=1,t;i<=r;i++) for(int j=1;j<=c;j++) t = getint() , sum[t][i][j] += t , ++siz[t][i][j];
        build();
        for(int i=1,x,y,xx,yy,ned,ans;i<=m;i++) {
            x = getint() , y = getint() , xx = getint() , yy = getint() , ned = getint() , ans = solve(x,y,xx,yy,ned);
            if( !~ans ) puts("Poor QLW");
            else printf("%d\n",ans);
        }
    }
}

namespace Task2 {
    const int maxn=5e5+1e2,maxe=1e7+1e2,lim=2e4;
    struct PersistentSegmentTree {
        int lson[maxe],rson[maxe],siz[maxe],cnt;
        lli sum[maxe];
        inline void insert(int &pos,int pre,int l,int r,const int &tar) {
            sum[pos=++cnt] = sum[pre] + tar , siz[pos] = siz[pre] + 1;
            if( l == r ) return;
            const int mid = ( l + r ) >> 1;
            tar <= mid ? ( rson[pos] = rson[pre] , insert(lson[pos],lson[pre],l,mid,tar) ) : ( lson[pos] = lson[pre] , insert(rson[pos],rson[pre],mid+1,r,tar) );
        }
        inline int query(int pos,int pre,int l,int r,int ned) {
            if( ned > sum[pos] - sum[pre] ) return -1; // unreachable .
            if( l == r ) return ( ned + l - 1 ) / l;
            const int mid = ( l + r ) >> 1;
            if( ned <= sum[rson[pos]] - sum[rson[pre]] ) return query(rson[pos],rson[pre],mid+1,r,ned);
            else return siz[rson[pos]] - siz[rson[pre]] + query(lson[pos],lson[pre],l,mid,ned-sum[rson[pos]]+sum[rson[pre]]);
        }
    }pst;
    int root[maxn];
    inline void work() {
        for(int i=1;i<=c;i++) pst.insert(root[i],root[i-1],0,lim,getint());
        for(int i=1,l,r,ans;i<=m;i++) {
            getint() , l = getint() , getint() , r = getint() , ans = pst.query(root[r],root[l-1],0,lim,getint());
            if( !~ans ) puts("Poor QLW");
            else printf("%d\n",ans);
        }
    }
}

int main() {
    r = getint() , c = getint() , m = getint();
    r == 1 ? Task2::work() : Task1::work();
    return 0;
}