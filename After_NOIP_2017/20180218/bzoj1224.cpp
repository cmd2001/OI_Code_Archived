#include<cstdio>
const int maxn=55;
const double eps=1e-10;

double sum[maxn],tar;
int n,m,ans;

inline void dfs(int pos,int siz,double now) {
    if( now + sum[pos+(n-siz)-1] - sum[pos-1] < tar - eps || now + sum[m] - sum[m-(n-siz)] > tar + eps ) return;
    if( siz == n ) {
        ++ans;
        return;
    }
    if( pos > m ) return;
    dfs(pos+1,siz,now);
    dfs(pos+1,siz+1,now+1.0/pos);
}

int main() {
    static double x,y;
    scanf("%d%d%lf%lf",&n,&m,&x,&y) , tar = x / y;
    for(int i=1;i<=m;i++) sum[i] = sum[i-1] + 1.0 / i;
    dfs(1,0,0);
    printf("%d\n",ans);
    return 0;
}

