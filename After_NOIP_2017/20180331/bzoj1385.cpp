#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e4+1e2;

int in[maxn];
inline int gcd(int x,int y) {
    if( ! ( x && y ) ) return x | y;
    register int t;
    while( t = x % y ) x = y , y = t;
    return y;
}

int main() {
    static int T,n,now;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        now = in[2] / gcd(in[1],in[2]);
        for(int i=3;i<=n;i++) now /= gcd(now,in[i]);
        puts(now==1?"YES":"NO");
    }
    return 0;
}