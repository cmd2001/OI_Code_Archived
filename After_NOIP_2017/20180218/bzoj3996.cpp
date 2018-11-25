#include<cstdio>

int main() {
    static int n,sum,x;
    scanf("%d",&n);
    for(int i=1;i<=n*n;i++) scanf("%d",&x) , sum += x;
    for(int i=1;i<=n;i++) scanf("%d",&x) , sum -= x;
    printf("%d\n",sum);
    return 0;
}
