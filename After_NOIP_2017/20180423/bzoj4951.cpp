#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
const int maxn=5e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

struct Point {
    int x,y;
    friend bool operator < (const Point &a,const Point &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
}pro[maxn],usr[maxn];

inline int fix(Point* dst,int len,bool tpe) { // tpe = 0 solve provider by pushing stack , cmp = 1 solve user by poping stack .
    static Point stk[maxn];
    std::sort(dst+1,dst+1+len);
    int top = 0;
    if( !tpe ) {
        for(int i=1;i<=len;i++) if( !top || stk[top].y > dst[i].y ) stk[++top] = dst[i];
    } else {
        for(int i=1;i<=len;i++) {
            while( top && stk[top].y <= dst[i].y ) --top;
            stk[++top] = dst[i];
        }
    }
    memcpy(dst+1,stk+1,sizeof(Point)*top);
    return top;
}

lli ans;

inline lli calc(const Point &pro,const Point &usr) {
    if( usr.x < pro.x && usr.y < pro.y ) return -inf;
    return (lli) ( usr.x - pro.x ) * ( usr.y - pro.y );
}
inline void solve(int pl,int pr,int ul,int ur) {
    if( pl == pr || ul == ur ) {
        for(int i=pl;i<=pr;i++) for(int j=ul;j<=ur;j++) ans = std::max( ans , calc(pro[i],usr[j]) );
        return;
    }
    int pmid = pl , umid = ( ul + ur ) >> 1;
    lli cur = -inf, cal;
    for(int i=pl;i<=pr;i++)
        if( ( cal = calc(pro[i],usr[umid]) ) > cur ) cur = cal , pmid = i;
    ans = std::max( ans , cur );
    if( ul < umid ) solve(pl,pmid,ul,umid-1);
    if( umid < ur ) solve(pmid,pr,umid+1,ur);
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d",&pro[i].x,&pro[i].y);
    for(int i=1;i<=m;i++) scanf("%d%d",&usr[i].x,&usr[i].y);
    n = fix(pro,n,0) , m = fix(usr,m,1);
    solve(1,n,1,m) , printf("%lld\n",ans);
    return 0;
}

