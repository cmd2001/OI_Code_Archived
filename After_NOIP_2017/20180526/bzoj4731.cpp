#include<cstdio>
#include<cctype>
typedef long long int lli;
const int maxn=1e4+1e2,maxm=1e6+1e2;

lli a[maxn],c[maxm];
int n,m;

inline char nextchar() {
    static const int BS = 1 << 23;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline lli getint() {
    lli ret = 0 , fix = 1;
    char ch;
    while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret * fix;
}

int main() {
    n = getint();
    for(int i=0;i<n;i++) a[i] = getint();
    m = getint() , a[n++] = m;
    for(int i=0;i<m;i++) c[i] = getint();
    for(int i=0,pi=1;i<n;i++) if( a[i] != 1 ) {
        for(int j=m-1;~j;j--) if( j % ( pi * a[i] ) >= pi ) c[j] -= c[j-pi];
        if( (lli) pi * a[i] >= m ) break;
        pi *= a[i];
    }
    printf("%d\n",--n);
    for(int i=0;i<n;i++) printf("%lld ",a[i]);
    printf("\n%d\n",m);
    for(int i=0;i<m;i++) printf("%lld ",c[i]);
    putchar('\n');
    return 0;
}
