#include<cstdio>
#include<cctype>

inline int gcd(int x,int y) {
    if( ! ( x && y ) ) return x | y;
    register int t;
    while( t = x % y ) x = y , y = t;
    return y;
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret= ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    static int n,ans;
    for(n=getint();n--;ans=gcd(ans,getint()));
    printf("%d\n",ans);
}

