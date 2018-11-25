#include<cstdio>
using namespace std;

int main() {
    static int n,rr;
    scanf("%d",&n);
    printf("%d\n",n*(n-1)>>1);
    rr = n >> 1;
    for(int r=1;r<=rr;r++)
        for(int st=0;st<n;st++)
            printf("%d %d %d\n",st+1,(st+r)%n+1,(st+r+r)%n+1);
}