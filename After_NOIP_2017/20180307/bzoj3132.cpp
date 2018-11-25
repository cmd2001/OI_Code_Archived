#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=2051;

int n,m; // we should ++n,++m first .
class SquareBinaryIndexTree {
    private:
        int dat[maxn][maxn];
        #define lowbit(x) (x&-x)
        inline void update(int* dst,int pos,int x) {
            while( pos <= m ) dst[pos] += x , pos += lowbit(pos);
        }
        inline int query(int* dst,int pos) {
            int ret = 0;
            while( pos ) ret += dst[pos] , pos -= lowbit(pos);
            return ret;
        }
    public:
        inline void update(int x,int y,int val) {
            while( x <= n ) update(dat[x],y,val) , x += lowbit(x);
        }
        inline int query(int x,int y) {
            int ret = 0;
            while( x ) ret += query(dat[x],y) , x -= lowbit(x);
            return ret;
        }
        SquareBinaryIndexTree() {
            memset(dat,0,sizeof(dat));
        }
}a,ai,aj,aij;

inline void update(int x,int y,int val) {
    a.update(x,y,val) , aij.update(x,y,val*x*y) ,
    ai.update(x,y,val*x) , aj.update(x,y,val*y) ;
}
inline int query(int x,int y) {
    int ret = 0;
    ret += x * y * a.query(x,y) , ret += aij.query(x,y) ,
    ret -= y * ai.query(x,y) , ret -= x * aj.query(x,y) ;
    return ret;
}
inline void update(int sx,int sy,int tx,int ty,int val) {
    ++tx , ++ty;
    update(tx,ty,val) , update(sx,sy,val) ,
    update(sx,ty,-val) , update(tx,sy,-val) ;
}
inline int query(int sx,int sy,int tx,int ty) {
    ++tx , ++ty;
    int ret = 0;
    ret += query(tx,ty) + query(sx,sy) ,
    ret -= query(sx,ty) + query(tx,sy) ;
    return ret;
}

int main() {
    static int sx,sy,tx,ty,val;
    static char o[10];
    scanf("%*s%d%d",&n,&m) , ++n , ++m;
    while( scanf("%s%d%d%d%d",o,&sx,&sy,&tx,&ty) == 5 ) {
        if( *o == 'L' ) {
            scanf("%d",&val) ,
            update(sx,sy,tx,ty,val);
        } else printf("%d\n",query(sx,sy,tx,ty));
    }
    return 0;
}
