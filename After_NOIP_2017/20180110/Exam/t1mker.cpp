#include<bits/stdc++.h>
using namespace std;

inline int _rand(int r) {
    return rand() % r + 1;
}

int main() {
    freopen("dat.txt","w",stdout);
    //srand(time(0));
    srand((20010128^20010425)*time(0));
    int n = 1000 , m = 10;
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++)
        printf("%d%c",_rand(n>>1)+(2147483647>>1),i!=n?' ':'\n');
    while(m--)
        printf("%d\n",_rand(n));
    return fclose(stdout);
}