#include<cstdio>
#include<algorithm>
const int maxn=2e5+1e2;

int a[maxn],b[maxn],sou[maxn],tar[maxn],swa[maxn][2],swb[maxn][2],n,al,bl;

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i) , sou[a[i]] = i;
    for(int i=1;i<=n;i++) scanf("%d",b+i) , tar[b[i]] = i;
    for(int i=1,t;i<=n;i++) if( a[i] != b[i] ) {
        if( tar[a[i]] >= sou[b[i]] ) std::swap(a[i],a[t=sou[b[i]]]) , sou[a[t]] = t , sou[a[i]] = i , swa[++al][0] = i , swa[al][1] = t;
        else std::swap(b[i],b[t=tar[a[i]]]) , tar[b[t]] = t , tar[b[i]] = i , swb[++bl][0] = i , swb[bl][1] = t;
    }
    printf("%d\n",al+bl);
    for(int i=1;i<=al;i++) printf("%d %d\n",swa[i][0],swa[i][1]);
    for(int i=bl;i;i--) printf("%d %d\n",swb[i][0],swb[i][1]);
    return 0;
}
