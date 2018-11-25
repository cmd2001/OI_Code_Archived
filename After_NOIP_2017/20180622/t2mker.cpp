#include<bits/stdc++.h>
using namespace std;
bool vis[20][20];

inline int _(int r) {
    return rand() % r + 1;
}
int main() {
    const int n = 17 , m = 50;
    printf("%d %d\n",n,m);
    for(int i=1;i<=m;i++) {
        int a = _(n) , b = _(n);
        while( a == b || vis[min(a,b)][max(a,b)]) a = _(n) , b = _(n);
        printf("%d %d\n",min(a,b),max(a,b)) , vis[min(a,b)][max(a,b)] = 1;
    }
    return 0;
}