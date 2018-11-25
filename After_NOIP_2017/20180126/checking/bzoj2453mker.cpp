#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4;
int n = 5000 , m = 5000 , r = 5000;

inline int _rand(int lim = r) {
    return rand() % lim + 1;
}


int main() {
    srand((unsigned long long)new char);
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++)
        printf("%d%c",_rand(),i!=n?' ':'\n');
    for(int j=1;j<=m;j++) {
        if( j < m / 2 || ( rand() & 1 ) ) {
            printf("R %d %d\n",_rand(n),_rand());
        } else {
            int x = _rand(n) , y = _rand(n);
            if( x > y ) swap(x,y);
            printf("Q %d %d\n",x,y);
        }
    }
    return 0;
}
