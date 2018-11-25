#pragma GCC optimize(3)
#include<cstdio>
#include<bitset>
const int maxn=1e8+1e2;
std::bitset<maxn> vis;

long long h;
int a,b,c,ans;


int main() {
    scanf("%lld%d%d%d",&h,&a,&b,&c);
    if( a == 1 || b == 1 || c == 1 ) return printf("%lld\n",h),0;
    for(int i=0;a*i<h;i++) {
        if( vis[a*i] ) break;
        for(int j=0;a*i+b*j<h;j++) {
            if( vis[a*i+b*j] ) break;
            for(int k=0;a*i+b*j+k*c<h;k++) {
                if( vis[a*i+b*j+k*c] ) break;
                vis[a*i+b*j+k*c] = 1;
            }
        }
    }
    printf("%llu\n",vis.count());
    return 0;
}
