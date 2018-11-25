#include<cstdio>
#include<cctype>
const int maxn=3e2+1e1,maxc=1e2+1e1;

int in[maxn][maxn],n,m,q;

struct LinearBinaryIndexTree {
    int dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,int x) {
        while( pos <= m ) dat[pos] += x , pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while(pos) ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
    #undef lowbit
};

struct SquareBinaryIndexTree {
    LinearBinaryIndexTree dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int px,int py,int x) {
        while( px <= n ) dat[px].update(py,x) , px += lowbit(px);
    }
    inline int query(int px,int py) {
        int ret = 0;
        while( px ) ret += dat[px].query(py) , px -= lowbit(px);
        return ret;
    }
    #undef lowbit
}bit[maxc];

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) bit[in[i][j]=getint()].update(i,j,1);
    scanf("%d",&q);
    for(int i=1,o,x,y,xx,yy,c;i<=q;i++) {
        o = getint() , x = getint() , xx = y = getint();
        if( o == 1 ) bit[in[x][y]].update(x,y,-1) , bit[in[x][y]=getint()].update(x,y,1);
        else y = getint() , yy = getint() , c = getint() , --x , --y , printf("%d\n",bit[c].query(xx,yy)+bit[c].query(x,y)-bit[c].query(x,yy)-bit[c].query(xx,y));
    }
    return 0;
}
