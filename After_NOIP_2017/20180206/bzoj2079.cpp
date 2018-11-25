#include<cstdio>
#define bool unsigned char
const int maxn=2e5+1e2;

bool vis[maxn];

int main() {
    static int n,m,x;
    static bool ans = 1;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m<<1;i++) {
        scanf("%d",&x);
        vis[x] = 1;
    }
    for(int i=1;i<=n;i++)
        ans &= vis[i];
    puts(ans?"TAK":"NIE");
    return 0;
}
