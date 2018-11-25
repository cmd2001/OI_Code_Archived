#include<cstdio>
const int maxn=1e2+1e1;
int tim[maxn];
int main() {
    static int a,b,c,ans;
    scanf("%d%d%d",&a,&b,&c);
    for(int i=1;i<=a;i++) for(int j=1;j<=b;j++) for(int k=1;k<=c;k++) ++tim[i+j+k];
    for(int i=1;i<=a+b+c;i++) if( tim[i] > tim[ans] ) ans = i;
    printf("%d\n",ans);
}
