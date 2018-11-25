#include<bits/stdc++.h>
using namespace std;

inline int _rand(int l) {
    return rand() % l + 1;
}

int main() {
    srand(time(0));
    const int n = 1e2;
    freopen("dat.txt","w",stdout);
    printf("%d %d %d\n",n,n,n);
    for(int i=1;i<=n;i++)
        printf("%d%c",_rand(n),i!=n?' ':'\n');
    for(int i=1;i<=n;i++)
        printf("%d %d\n",_rand(n),_rand(n));
    return 0;
}