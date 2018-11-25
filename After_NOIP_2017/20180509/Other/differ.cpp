#include<bits/stdc++.h>
using namespace std;
bitset<10100> vis;

int main() {
    static int x;
    freopen("my.txt","r",stdin);
    while( scanf("%d",&x) == 1 ) vis[x] = 1;
    freopen("rbq.txt","r",stdin);
    while( scanf("%d",&x) == 1 ) if(!vis[x]) printf("%d\n",x);
    return 0;
}