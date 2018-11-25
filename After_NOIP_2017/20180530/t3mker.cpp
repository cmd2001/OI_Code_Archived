#include<bits/stdc++.h>
using namespace std;

inline int _(int r=4) {
    return rand() % r;
}

int main() {
    srand((unsigned long long)new char);
    puts("1");
    static int n = 10 , m = 5 , k = 3;
    printf("%d %d %d\n",n,k,m);
    for(int i=1;i<=n;i++) printf("%d%c",_(k),i!=n?' ':'\n');
    for(int i=1,o,l,r;i<=m;i++) {
        o = _(3) + 1, l = _(n) + 1 , r = _(n) + 1;
        printf("%d %d %d",o,min(l,r),max(l,r));
        if( o != 3 ) printf(" %d",_(k));
        puts("");
    }
    return 0;
}
