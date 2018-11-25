#include<cstdio>
#include<bitset>
#include<cmath>
typedef long long int lli;
using namespace std;
const int maxn=1e9+1e2;

bitset<maxn> vis;

inline int calc(int lim) {
    vis &= 0;
    for(int i=1;i<=1000;i++)
        for(int j=i+1,sq=sqrt(lim/i);j<=sq;j++)
            for(lli k=j*j;i*k<=lim;k*=j) vis[i*k] = 1;
    return vis.count();
}

int main() {
    static int l,r;
    freopen("rinascimento.in","r",stdin);
    freopen("rinascimento.out","w",stdout);
    scanf("%d%d",&l,&r) , printf("%d\n",calc(r)-calc(l-1));
    fclose(stdout);
    return 0;
}
