#include<cstdio>
#include<algorithm>
const int maxn=1e3+1e2;
const int inf=0x3f3f3f3f;

struct Node {
    int r,t;
    friend bool operator < (const Node &a,const Node &b) {
        return a.r < b.r;
    }
}ns[maxn];

int main() {
    static int n,now;
    scanf("%d",&n) , now = inf;
    for(int i=1;i<=n;i++) scanf("%d%d",&ns[i].t,&ns[i].r);
    std::sort(ns+1,ns+1+n);
    for(int i=n;i;i--) now = std::min(now,ns[i].r) - ns[i].t;
    printf("%d",now>0?now:-1);
    return 0;
}
