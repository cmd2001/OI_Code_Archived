#include<bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));
    freopen("dat.txt","w",stdout);
    const int n=rand()%100+1 , m=rand()%100+1;
    printf("%d %d\n",n,m);
    for(int t=1;t<=3;t++)
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=m;j++)
                printf("%d%c",(rand()%1000+1),j!=m?' ':'\n');
        }
}