#include<bits/stdc++.h>
using namespace std;

inline int _rand(int r) {
    return rand() % r + 1;
}
inline int _rand() {
    //return rand() % 10 + 1;
    return rand() % 100000000 + 1;
}

int main() {
    srand((unsigned long long)new char);
    //freopen("dat.txt","w",stdout);
    const int n = 80000 , q = 80000;
    printf("%d %d\n",n,q);
    for(int i=1;i<=n;i++)
        printf("%d%c",_rand(),i!=n?' ':'\n');
    for(int i=2;i<=n;i++)
        printf("%d %d\n",i,_rand(i-1));
    for(int i=1;i<=q;i++) {
        int k = rand() % ((n/2) ) ;
        if( k ) printf("%d %d %d\n",k,_rand(n),_rand(n));
        else printf("%d %d %d\n",k,_rand(n),_rand());
    }
    
    return 0;
}