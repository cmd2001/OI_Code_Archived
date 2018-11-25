#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
const int maxn=1e4+1e2,maxw=131073;
const int inf=0x3f3f3f3f;

int in[maxn],f[maxw];
bool vis[23];
int n,cb,su,k;

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0; char ch;
    while( !isdigit(ch=nextchar()) ) ;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    n = getint() , k = getint();
    for(int i=1;i<=n;i++) {
        in[i] = getint();
        for(int t=0;t<20;t++) if( ( in[i] & ( 1 << t ) ) && !vis[t] ) {
            cb += vis[t] = 1 , su |= 1 << t;
        }
    }
    if( n - k >= cb ) return printf("%d\n",su),0;
    memset(f,0x3f,sizeof(f)) , *f = 0;
    for(int i=1;i<=n;i++) for(int j=0;j<maxw;j++) if( f[j] != inf ) f[j|in[i]] = min(f[j|in[i]],f[j]+1);
    for(int j=maxw-1;~j;j--) if( f[j] <= n - k ) return printf("%d\n",j) , 0;
    return 0;
}

