#include<bits/stdc++.h>
using namespace std;
const int n = 10000 , m = 20000;

int x[n+10];
bitset<n+1> vis[n+1];

int main() {
    srand(time(0));
    freopen("dat.txt","w",stdout);
    for(int T=1;T<=10;T++) {
        printf("%d %d\n",n,m);
        for(int i=1;i<=n;i++)
            vis[i] &= 0;
        if( T & 1 ) {
            for(int i=1,l,r;i<=m;i++) {
                l = rand() % n + 1 , r = rand() % n + 1;
                while( vis[l][r] )
                    l = rand() % n + 1 , r = rand() % n + 1;
                printf("%d %d\n",l,r);
            }
        }
        else {
            for(int i=1;i<=n;i++)
                x[i] = i;
            random_shuffle(x+1,x+1+n);
            for(int i=1;i<=n;i++) {
                vis[i][x[i]] = 1;
                printf("%d %d\n",i,x[i]);
            }
            for(int i=1,l,r;i<=n;i++) {
                l = rand() % n + 1 , r = rand() % n + 1;
                while( vis[l][r] )
                    l = rand() % n + 1 , r = rand() % n + 1;
                printf("%d %d\n",l,r);
            }
        }
    }
    return fclose(stdout);
}