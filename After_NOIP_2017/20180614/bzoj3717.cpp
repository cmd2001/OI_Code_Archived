#include<cstdio>
#include<cstring>
#include<algorithm>
#include<functional>
const int maxn=1e2+1e1,maxl=1<<24;
const int inf=0x3f3f3f3f;

int v[maxn];
int f[maxl],g[maxl],w[maxl];

inline void update(int sta,int ff,int gg) {
    if( ff < f[sta] || ( ff == f[sta] && gg > g[sta] ) ) f[sta] = ff , g[sta] = gg;
}

int main() {
    static int n,m,fs;
    scanf("%d%d",&n,&m) , memset(f,0x3f,sizeof(f)) , fs = 1 << n;
    for(int i=0;i<n;i++) scanf("%d",w+(1<<i));
    for(int i=1;i<=m;i++) scanf("%d",v+i);
    std::sort(v+1,v+1+m,std::greater<int>());
    f[0] = 0 , g[0] = -1;
    #define lowbit(x) (x&-x)
    for(int i=0;i<fs;i++) {
        for(int j=i,t=lowbit(j);j;j-=t,t=lowbit(j)) {
            if( f[i^t] == inf ) continue;
            if( w[t] <= g[i^t] ) update(i,f[i^t],g[i^t]-w[t]);
            else if( w[t] <= v[f[i^t]+1] ) update(i,f[i^t]+1,v[f[i^t]+1]-w[t]);
        }
    }
    f[fs-1] == inf ? puts("NIE") : printf("%d\n",f[fs-1]);
    return 0;
}
