#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=3e5+1e2;
const int inf=0x3f3f3f3f;

int in[maxn];

inline int getint() {
    int ret = 0; char ch;
    while( !isdigit(ch=getchar()) ) ;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    static int n,m;
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) in[i] = getint();
    scanf("%*s");
    for(int i=1;i<=n;i++) if( in[i] < in[i-1] ) in[i] += min( in[i-1] - in[i] , m );
    for(int i=1;i<=n;i++) printf("%d%c",in[i],i!=n?' ':'\n');
    return 0;
}

