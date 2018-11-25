#pragma GCC optimize(3)
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#include<cstdio>
#include<cctype>
#define maxn 50011
#define lli long long int

int in[maxn];

inline lli calc(int l,int r) {
    register lli ret = 0 , now = 0;
    register int *ll = in + l , *rr = in + r;
    while( ll <= rr )
        now += *ll++ ,
        now = now > 0 ? now : 0 ,
        ret = ret > now ? ret : now;
    return ret;
}
inline void update(int l,int r,register int x) {
    register int *ll = in + l , *rr = in + r;
    while( ll <= rr )
        *ll++ += x;
}
inline char nextchar() {
    static char buf[1<<22],*st=buf+(1<<22),*ed=buf+(1<<22);
    if( st == ed ) ed = buf + fread(st=buf,1,1<<22,stdin);
    return st == ed ? -1 : *st++;
}
inline void printchar(char x) {
    static char buf[1<<22],*st=buf,*ed=buf+(1<<22);
    if( x == -1 ) {
        fwrite(buf,1,st-buf,stdout);
        st = buf;
        return;
    }
    if( st == ed ) fwrite(st=buf,1,1<<22,stdout);
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
inline char realchar() {
    char ret;
    while( !isalpha(ret=nextchar()) );
    return ret;
}
inline int getint() {
    int ret = 0 , fix = 1 , ch;
    while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -1 : fix;
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret * fix;
}

int main() {
    static int n,m,l,r,x;
    n = getint() , m = getint();
    for(int i=1;i<=n;++i)
        in[i] = getint();
    while( m-- ) {
        if( realchar() == 'Q' ) {
            l = getint() , r = getint();
            printint(calc(l,r));
        } else {
            l = getint() , r = getint() , x = getint();
            update(l,r,x);
        }
    }
    printchar(-1);
    return 0;
}
