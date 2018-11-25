#include<bits/stdc++.h>
using namespace std;

int fa[50010];

int main() {
    freopen("dat.txt","w",stdout);
    const int n = 10 ;
    int m = 0;
    
    for(int i=2;i<=n;i++)
        if( rand()&1 )
            fa[i] = rand() % i + 1 , ++m;
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++)
        printf("%d\n",(rand()-rand())%100);
    for(int i=1;i<=n;i++)
        if( fa[i] )
            printf("%d %d\n",fa[i],i);
    return 0;
}