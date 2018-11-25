#include<bits/stdc++.h>
using namespace std;
const int n = 100 , m = 100 , k = 20;
int vis[210][210];

inline int _rand(int r) {
    return rand() % r + 1;
}

int main() {
    srand((unsigned long long)new char);
    printf("%d %d %d\n",n,m,k);
    for(int i=1;i<=n;i++)
        printf("%d%c",_rand(m),i!=n?' ':'\n');
    for(int i=1;i<=m;i++)
        printf("%d%c",_rand(n),i!=m?' ':'\n');
    for(int i=1;i<=k;i++) {
        int x = _rand(n) , y = _rand(m);
        while( vis[x][y] ) x = _rand(n) , y = _rand(m);
        vis[x][y] = 1;
        printf("%d %d\n",x,y);
    }
    return 0;
}
