#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e5+1e2,maxl=20,lim=17;
 
double fac[maxl],c[maxl][maxl];
 
struct LCT {
    struct Node {
        double dat[maxl];
         
        inline void in(const double &a,const double &b,const int &tpe) {
            static double pa[maxl],pb[maxl];
            if( tpe != 3 ) {
                *pa = *pb = 1;
                for(int i=1;i<=lim;i++) pa[i] = pa[i-1] * a , pb[i] = pb[i-1] * b;
            }
            memset(dat,0,sizeof(dat));
            if( tpe == 1 ) {
                for(int i=1,t=1;i<=lim;i+=2,t=-t)
                    for(int j=0;j<=i;j++)
                        dat[j] += pa[j] * pb[i-j] * c[i][j] * t / fac[i];
            } else if( tpe == 2 ) {
                for(int i=0;i<=lim;i++)
                    for(int j=0;j<=i;j++)
                        dat[j] += pa[j] * pb[i-j] * c[i][j] / fac[i];
            } else if( tpe == 3 ) {
                dat[1] = a , dat[0] = b;
            }
        }
        inline double calc(const double &x) {
            static double pows[maxl];
            *pows = 1;
            for(int i=1;i<=lim;i++) pows[i] = pows[i-1] * x;
            double ret = 0;
            for(int i=0;i<=lim;i++) ret += dat[i] * pows[i];
            return ret;
        }
         
        friend Node operator + (const Node &a,const Node &b) {
            Node ret; memset(ret.dat,0,sizeof(ret.dat));
            for(int i=0;i<=lim;i++) ret.dat[i] = a.dat[i] + b.dat[i];
            return ret;
        }
    }dat[maxn],sum[maxn];
    int ch[maxn][2],fa[maxn],rev[maxn];
    inline void apply(int pos) {
        if( !pos ) return;
        rev[pos] ^= 1 ,
        swap(ch[pos][0],ch[pos][1]);
    }
    inline void push(int pos) {
        if( !rev[pos] ) return;
        apply(ch[pos][0]) , apply(ch[pos][1]) ,
        rev[pos] = 0;
    }
    inline void update(int x) {
        sum[x] = dat[x];
        if( ch[x][0] ) sum[x] = sum[x] + sum[ch[x][0]];
        if( ch[x][1] ) sum[x] = sum[x] + sum[ch[x][1]]; 
    }
    inline bool isrt(int x) {
        return x != ch[fa[x]][0] && x != ch[fa[x]][1];
    }
    inline bool gid(int x) {
        return x == ch[fa[x]][1];
    }
    inline void rotate(int x) {
        push(fa[x]) , push(x);
        const int f = fa[x] , id = gid(x);
        fa[x] = fa[f];
        if( !isrt(f) ) ch[fa[f]][gid(f)] = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        ch[x][id^1] = f , fa[f] = x;
        update(f) , update(x);
    }
    inline void pushchain(int x) {
        if( !isrt(x) ) pushchain(fa[x]);
        push(x);
    }
    inline void upchain(int x) {
        while(1) {
            update(x);
            if( isrt(x) ) break;
            x = fa[x];
        }
    }
    inline void splay(int x) {
        pushchain(x);
        while( !isrt(x) ) {
            if( !isrt(fa[x]) ) rotate(fa[x]);
            rotate(x);
        }
    }
    inline void access(int x) {
        int y = 0;
        while( x ) {
            splay(x) , ch[x][1] = y , update(x);
            y = x , x = fa[x];
        }
    }
    inline void mkrt(int x) {
        access(x) , splay(x) , apply(x);
    }
    inline void link(int x,int y) {
        mkrt(x) , fa[x] = y;
    }
    inline void cut(int x,int y) {
        mkrt(x) , access(y) , splay(y);
        ch[y][0] = fa[x] = 0 , update(y);
    }
    inline int findfa(int x) {
        while( fa[x] ) x = fa[x];
        return x;
    }
    inline Node query(int x,int y) {
        mkrt(x) , access(y) , splay(y);
        return sum[y];
    }
}T;
inline void pre() {
    *fac = 1;
    for(int i=1;i<=lim;i++) fac[i] = fac[i-1] * i;
    c[0][0] = 1;
    for(int i=1;i<=lim;i++) {
        c[i][0] = 1;
        for(int j=1;j<=i;j++) c[i][j] = c[i-1][j-1] + c[i-1][j];
    }
}
 
int main() {
    static int n,m;
    static char o[10];
    static double a,b;
    pre();
    scanf("%d%d%*s",&n,&m);
    for(int i=1,t;i<=n;i++) {
        scanf("%d%lf%lf",&t,&a,&b);
        T.dat[i].in(a,b,t);
    }
    for(int i=1,t,x,y;i<=m;i++) {
        scanf("%s",o);
        if( *o == 'a' ) {
            scanf("%d%d",&x,&y) , ++x , ++y;
            T.link(x,y);
        } else if( *o == 't' ) {
            scanf("%d%d%lf",&x,&y,&a) , ++x , ++y;
            if( T.findfa(x) != T.findfa(y) ) puts("unreachable");
            else {
                LCT::Node ans = T.query(x,y);
                printf("%.8e\n",ans.calc(a));
            }
        } else if( *o == 'm' ) {
            scanf("%d%d%lf%lf",&x,&t,&a,&b) , ++x;
            T.splay(x);
            T.dat[x].in(a,b,t);
        } else if( *o == 'd' ) {
            scanf("%d%d",&x,&y) , ++x , ++y;
            T.cut(x,y);
        }
    }
    return 0;
}
