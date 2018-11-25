#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
const int maxn=2e4+1e2,maxw=43;

int lson[maxn],rson[maxn];
lli f[maxn][maxw][maxw],c[maxn],a[maxn],b[maxn];
int n,m;

inline lli calc(int pos,int x,int y) {
    if( pos >= n ) return c[pos-n] * ( a[pos-n] + x ) * ( b[pos-n] + y );
    return f[pos][x][y];
}

inline void dfs(int pos,int x,int y) {
    if( pos >= n ) return;
    dfs(lson[pos],x+1,y) , dfs(rson[pos],x,y+1);
    for(int i=0;i<=x;i++) for(int j=0;j<=y;j++) f[pos][i][j] = std::min( calc(lson[pos],i+1,j) + calc(rson[pos],i,j) , calc(lson[pos],i,j) + calc(rson[pos],i,j+1) );
}

int main() {
    scanf("%d",&n) , memset(f,0x3f,sizeof(f));
    for(int i=1,s,t;i<n;i++) {
        scanf("%d%d",&s,&t);
        lson[i] = s > 0 ? s : n - s , rson[i] = t > 0 ? t : n - t;
    }
    for(int i=1;i<=n;i++) scanf("%lld%lld%lld",a+i,b+i,c+i);
    dfs(1,0,0) , printf("%lld\n",f[1][0][0]);
    return 0;
}

