#include<cstdio>
#include<algorithm>
const int maxn=2e5+1e2;

int in[maxn],p[maxn],mi[maxn],mx[maxn],cnt;

inline bool cmp(int x,int y) {
    return in[x] == in[y] ? x < y : in[x] < in[y];
}
int main() {
    static int n,fil,ans,lst;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , p[i] = i;
    std::sort(p+1,p+1+n,cmp);
    for(int i=1;i<=n;i++)
        if( i == 1 || in[p[i]] != in[p[i-1]] ) ++cnt , mi[cnt] = mx[cnt] = p[i];
        else mi[cnt] = std::min( mi[cnt] , p[i] ) , mx[cnt] = std::max( mx[cnt] , p[i] );
    for(int i=1;i<=cnt;i++)
        if( i == 1 ) ++ans , fil = 0 , lst = mi[i];
        else if( fil && mi[i] < lst ) ++ans , fil = 0 , lst = mi[i];
        else if( fil && mi[i] > lst ) lst = mx[i];
        else if( !fil && mx[i] > lst ) fil = 1 , lst = mx[i];
        else if( !fil && mx[i] < lst ) lst = mi[i];
   printf("%d\n",ans);
   return 0;
}
