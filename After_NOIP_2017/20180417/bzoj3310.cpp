#include<cstdio>
typedef long long int lli;
const int maxn=3e6+1e2;

int vis[maxn],n;

inline void mrk(int x,int y,int a,int b) {
    for(int i=1;i<=y;i++) vis[((lli)a*i+b)%n] += x;
}
inline void push() {
    for(int i=0;i<n-1;i++) if( vis[i] > 1 ) vis[i+1] += vis[i] - 1 , vis[i] = 1;
}

int main() {
    static int k;
    scanf("%d%d",&n,&k);
    for(int i=1,x,y,a,b;i<=k;i++) scanf("%d%d%d%d",&x,&y,&a,&b) , mrk(x,y,a,b);
    push();
    if( vis[n-1] > 1 ) vis[0] += vis[n-1] - 1 , vis[n-1] = 1 , push();
    for(int i=0;i<n;i++) if( !vis[i] ) return printf("%d\n",i),0;
    return 0;
}