#include<cstdio>
const int maxn=2e6+1e2;

char in[maxn];
int ca,cb,n,m,i;

int main() {
    scanf("%d%s",&m,in+1) , n = m >> 1;
    if( ! ( m & 1 ) ) return puts("NOT POSSIBLE") , 0;

    for(i=1;i<=n&&in[i]==in[i+n];i++);
    for(;i<=n&&in[i]==in[i+n+1];i++) ;
    ca = i > n;

    for(i=m;i>n+1&&in[i]==in[i-n];i--);
    for(;i>n+1&&in[i]==in[i-n-1];i--) ;
    cb = i <= n + 1;

    if( !ca && !cb ) return puts("NOT POSSIBLE") , 0;
    if( ca && cb ) {
        for(i=1;i<=n&&in[i]==in[i+n+1];i++);
        if( i <= n ) return puts("NOT UNIQUE") , 0;
        for(int i=1;i<=n;i++) putchar(in[i]);
    }
    else if(ca) for(int i=1;i<=n;i++) putchar(in[i]);
    else for(int i=n+2;i<=m;i++) putchar(in[i]);
    return putchar('\n') , 0;
}
