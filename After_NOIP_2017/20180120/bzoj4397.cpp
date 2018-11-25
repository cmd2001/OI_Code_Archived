#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=1e5+1e2;

int sum[maxn][3];

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,x;i<=n;i++) {
        scanf("%d",&x) , --x;
        memcpy(sum[i],sum[i-1],sizeof(sum[i-1]));
        ++sum[i][x];
    }
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d",&a,&b);
        for(int i=0;i<3;i++)
            printf("%d%c",sum[b][i]-sum[a-1][i],i!=2?' ':'\n');
    }
    return 0;
}