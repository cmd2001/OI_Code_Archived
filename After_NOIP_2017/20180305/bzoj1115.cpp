#include<cstdio>
const int maxn=1e3+1e2;

int in[maxn],n,ans;

int main() {
    static int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n) , ans = 0;
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        for(int i=n;i;i--) in[i] -= in[i-1];
        for(int i=n;i>0;i-=2) ans ^= in[i];
        puts(ans?"TAK":"NIE");
    }
    return 0;
}
