#pragma GCC optimize("O3")
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cctype>
#define lli long long int
const int maxn=1e5+1e2,maxb=650;

int srt[maxn];
int in[maxn],len;
int sum[maxb][maxn],pre[maxb][maxb];
int st[maxb],ed[maxb],bel[maxn],cnt;
int tim[maxn];
int  n,ans;
int rel = 0;

inline void gen() {
    for(int i=1;i<=n;i++) {
        ++tim[in[i]];
        if( i == ed[bel[i]] ) memcpy(sum[bel[i]],tim,sizeof(tim));
    }
    for(int i=1,ans;i<=cnt;i++) {
        memset(tim,0,sizeof(tim)) , ans = 0;
        for(int j=st[i];j<=n;j++) {
            ++tim[in[j]];
            if( (lli) tim[in[j]] * srt[in[j]] > (lli) tim[ans] * srt[ans] ) ans = in[j];
            if( j == ed[bel[j]] ) pre[i][bel[j]] = ans;
        }
    }
    memset(tim,0,sizeof(tim));
}
inline int seg(int a,int b,int pos) { // a - b +
    return sum[b][pos] - sum[a][pos] + tim[pos];
}
inline void query_part(int id,int a,int b,int l,int r) { // a - b +
    l = std::max( l ,st[id] ) , r = std::min( r , ed[id] );
    for(int i=l;i<=r;i++) {
        ++tim[in[i]];
        if( (lli) seg(a,b,in[i]) * srt[in[i]] > (lli) seg(a,b,ans) * srt[ans] ) ans = in[i];
        ++rel;
    }
}
inline void reset_part(int id,int l,int r) {
    l = std::max( l ,st[id] ) , r = std::min( r , ed[id] );
    for(int i=l;i<=r;i++) tim[in[i]] = 0;
}
inline lli query(int l,int r) {
    ans = 0;
    lli ret;
    if( bel[l] == bel[r] ) {
        query_part(bel[l],0,0,l,r);
        ret = (lli) srt[ans] * seg(0,0,ans);
        reset_part(bel[l],l,r);
    } else if( bel[r] == bel[l] + 1 ) {
        query_part(bel[l],0,0,l,r) ,
        query_part(bel[r],0,0,l,r) ;
        ret = (lli) srt[ans] * seg(0,0,ans);
        reset_part(bel[l],l,r) ,
        reset_part(bel[r],l,r) ;
    } else {
        ans = pre[bel[l]+1][bel[r]-1];
        query_part(bel[l],bel[l],bel[r]-1,l,r) ,
        query_part(bel[r],bel[l],bel[r]-1,l,r) ;
        ret = (lli) srt[ans] * seg(bel[l],bel[r]-1,ans);
        reset_part(bel[l],l,r) ,
        reset_part(bel[r],l,r) ;
    }
    return ret;
}
inline void init() {
    for(int i=1;i<=n;i++) srt[i] = in[i];
    std::sort(srt+1,srt+1+n) , len = std::unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++) in[i] = std::lower_bound(srt+1,srt+1+n,(lli)in[i]) - srt;
    int b = sqrt(n);
    b >>= 1 , b = std::max( b , 1 );
    for(int l=1,r;l<=n;l=r+1) {
        r = std::min( l + b - 1 , n ) , ++cnt;
        st[cnt] = l , ed[cnt] = r;
        for(int i=l;i<=r;i++) bel[i] = cnt;
    }
}

inline char nextchar() {
    static char buf[1<<21],*st=buf+(1<<21),*ed=buf+(1<<21);
    if( st == ed ) ed = buf + fread(st=buf,1,1<<21,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , fix = 1 , ch;
    while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -1 : fix;
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret * fix;
}
inline void printchar(char x) {
    static char buf[1<<15],*st=buf,*ed=buf+(1<<15);
    if( x == -1 ) {
        fwrite(buf,1,st-buf,stdout);
        st = buf;
        return;
    }
    if( st == ed ) fwrite(st=buf,1,1<<15,stdout);
    *st++ = x;
}
inline void printint(lli x) {
    static int stk[35],top;
    if( !x ) {
        printchar('0');
    } else {
        while( x ) stk[++top] = x % 10 , x /= 10;
        while( top ) printchar('0'+stk[top--]);
    }
    printchar('\n');
}

int main() {
    static int m;
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) in[i] = getint();
    init() , gen();
    for(int i=1,a,b;i<=m;i++) {
        a = getint() , b = getint();
        printint(query(a,b));
    }
    printchar(-1);
    return 0;
}
